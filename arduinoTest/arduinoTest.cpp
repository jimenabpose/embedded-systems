#include <string.h>
#include "etherShield.h"

#define PACKET_MAXSIZE 512

#define TIME_WAIT_TIMEOUT 30
#define ACK_TIMEOUT 30
#define ARP_TIMEOUT 30

#define IP_OCTETS 4
#define MAC_OCTETS 6

#define SENSORS_QTY 8
#define SENSOR_ON 1
#define SENSOR_OFF 0

#define CAR_PIN  5
#define CAR_PIN_OUTPUT  6

#define RAW_INFOPCK_SIZE sizeof(ip_t) + sizeof(int) \
	+ SENSORS_QTY * sizeof(individual_info_t)

typedef uint8_t sensors_t[SENSORS_QTY];

typedef enum {
    NO_COMMAND
} command_type_t;

typedef struct _command_t command_t;
typedef uint8_t ip_t[IP_OCTETS];

struct _command_t {
    command_type_t cmd;
    uint8_t args[512];
};

typedef enum {
  OCCUPIED, VACANT
} spot_state_t;

typedef uint32_t spot_id_t;

typedef struct _individual_info_t individual_info_t;

struct _individual_info_t {
  spot_id_t spot;
  spot_state_t state;
};

typedef individual_info_t info_packet_t[SENSORS_QTY];

info_packet_t packet;

uint16_t time_wait_counter;
uint16_t ack_wait_counter;
uint16_t arp_wait_counter;

typedef uint8_t raw_packet_t[RAW_INFOPCK_SIZE];

typedef enum {
  IDLE,
  AWAITING_ARP_REPLY,
  ARP_SUCCESS,
  AWAITING_SYNACK,
  SYN_SUCCESS,
  AWAITING_ACK,
  MESSAGE_RECIEVED,
  AWAITING_FINACK,
  AWAITING_FIN,
  TIME_WAIT
}client_state;

static uint8_t mymac[MAC_OCTETS] = {0x55,0x55,0x58,0x10,0x00,0x24};
static ip_t myip = {192,168,1,15};
static uint16_t my_port = 8080;

static ip_t server_ip = {192,168,1,1};
static uint8_t server_mac[MAC_OCTETS];
static uint16_t server_port = 8088;

bool sensors_updated;
sensors_t sensors;
bool command_arrived;
command_t command_fetched;

static bool not_expected_packet = false;

EtherShield es = EtherShield();

raw_packet_t raw_packet;

client_state curr_state;

uint16_t packet_length;

bool communicate_changes;

void setup(){

  /*initialize enc28j60*/
  es.ES_enc28j60Init(mymac);
  es.ES_enc28j60clkout(2); // change clkout from 6.25MHz to 12.5MHz

  delay(10);

  /* Magjack leds configuration, see enc28j60 datasheet, page 11 */
  // LEDA=green LEDB=yellow
  //
  // 0x880 is PHLCON LEDB=on, LEDA=on
  // enc28j60PhyWrite(PHLCON,0b0000 1000 1000 00 00);
  es.ES_enc28j60PhyWrite(PHLCON,0x880);
  delay(500);

  //
  // 0x990 is PHLCON LEDB=off, LEDA=off
  // enc28j60PhyWrite(PHLCON,0b0000 1001 1001 00 00);
  es.ES_enc28j60PhyWrite(PHLCON,0x990);
  delay(500);

  //
  // 0x880 is PHLCON LEDB=on, LEDA=on
  // enc28j60PhyWrite(PHLCON,0b0000 1000 1000 00 00);
  es.ES_enc28j60PhyWrite(PHLCON,0x880);
  delay(500);

  //
  // 0x990 is PHLCON LEDB=off, LEDA=off
  // enc28j60PhyWrite(PHLCON,0b0000 1001 1001 00 00);
  es.ES_enc28j60PhyWrite(PHLCON,0x990);
  delay(500);

  //
  // 0x476 is PHLCON LEDA=links status, LEDB=receive/transmit
  // enc28j60PhyWrite(PHLCON,0b0000 0100 0111 01 10);
  es.ES_enc28j60PhyWrite(PHLCON,0x476);
  delay(100);

  //init the ethernet/ip layer:
  es.ES_init_ip_arp_udp_tcp(mymac,myip,80);

  pinMode(A0, OUTPUT);
  not_expected_packet = false;

}

void loop() {
  digitalWrite(A1, LOW);

//  do {
    delay(1000);
//    handle_connection_status();
    if(packet_recieved() == true) {
//      checkout_pck();
      handle_input_pck();}
//    } else {
//      not_expected_packet = false;
//    }
//  }while(not_expected_packet);

//  read_sensors();

//  if( !communicate_changes && sensors_changed() == true) {
//    communicate_changes = true;
//  }

//  handle_output_pck();
//  digitalWrite(A1, HIGH);
}

void read_sensors() {

}

bool packet_recieved() {
  return ((packet_length =
    es.ES_enc28j60PacketReceive(PACKET_MAXSIZE, raw_packet)) != 0);
}
bool sensors_changed() {
        pinMode(CAR_PIN, INPUT);
	digitalWrite(CAR_PIN, LOW);
	pinMode(CAR_PIN_OUTPUT, OUTPUT);
	digitalWrite(CAR_PIN_OUTPUT, HIGH);
}
//void checkout_pck() {

//}

void handle_input_pck() {

  if(es.ES_eth_type_is_arp_and_my_ip(raw_packet, packet_length)){
//    if(es.ES_arp_packet_is_myreply_arp(raw_packet)
//      && curr_state == AWAITING_ARP_REPLY) {

//      int i;
//      for(i=0; i<MAC_OCTETS; i++){
//        server_mac[i] = raw_packet[ETH_SRC_MAC+i];
//      }
//      not_expected_packet = false;
//      curr_state = ARP_SUCCESS;
//    } else  {
      es.ES_make_arp_answer_from_request(raw_packet);
      not_expected_packet = true;

//    }
    return;
  }
  // check if ip packets (icmp or udp) are for us:
  if(es.ES_eth_type_is_ip_and_my_ip(raw_packet, packet_length)!=0){
    if(raw_packet[IP_PROTO_P]==IP_PROTO_ICMP_V
      && raw_packet[ICMP_TYPE_P]==ICMP_TYPE_ECHOREQUEST_V){
      // a ping packet, let's send pong
      es.ES_make_echo_reply_from_request(raw_packet, packet_length);
      not_expected_packet = true;
      return;
    }
//    switch(curr_state) {
//	case AWAITING_SYNACK:
//	  if(raw_packet[IP_PROTO_P] == IP_PROTO_TCP_V
//	    && raw_packet[TCP_FLAGS_P] == (TCP_FLAG_SYN_V|TCP_FLAG_ACK_V)) {
//	      es.ES_tcp_client_send_packet(
//          raw_packet,
//          server_port, my_port,
//          TCP_FLAG_ACK_V,
//          0, 0, 1, 0,
//          server_mac, server_ip
//          );
//      	  curr_state = SYN_SUCCESS;
//      }
//	  break;
//	case AWAITING_ACK:
//	  if(raw_packet[IP_PROTO_P] == IP_PROTO_TCP_V
//	    && raw_packet[TCP_FLAGS_P] == (TCP_FLAG_SYN_V|TCP_FLAG_ACK_V)) {
//	    es.ES_tcp_client_send_packet(
//	    raw_packet,
//	    server_port, my_port,
//	    TCP_FLAG_ACK_V,
//	    0, 0, packet_length, 0,
//	    server_mac, server_ip
//	    );
//	    curr_state = MESSAGE_RECIEVED;
//	  }
//	  break;
//	case AWAITING_FINACK:
//	  if(raw_packet[IP_PROTO_P] == IP_PROTO_TCP_V) {
//	    if (raw_packet[TCP_FLAGS_P] == (TCP_FLAG_FIN_V|TCP_FLAG_ACK_V)) {
//	      es.ES_tcp_client_send_packet(
//	      raw_packet,
//	      server_port, my_port,
//	      TCP_FLAG_ACK_V,
//	      0, 0, 0, 0,
//	      server_mac, server_ip
//	      );
//	      time_wait_counter = TIME_WAIT_TIMEOUT;
//	      curr_state = TIME_WAIT;
//	    } else if (raw_packet[TCP_FLAGS_P] == (TCP_FLAG_ACK_V)){
//	      ack_wait_counter = ACK_TIMEOUT;
//	      curr_state = AWAITING_FIN;
//	    }
//	  }
//
//	  break;
//	case AWAITING_FIN:
//	  es.ES_tcp_client_send_packet(
//	  raw_packet,
//	  server_port, my_port,
//	  TCP_FLAG_ACK_V,
//	  0, 0, 0, 0,
//	  server_mac, server_ip
//	  );
//	  curr_state = TIME_WAIT;
//	  break;
//	case TIME_WAIT:
//	  if (raw_packet[TCP_FLAGS_P] == (TCP_FLAG_ACK_V)){
//	    es.ES_tcp_client_send_packet(
//	    raw_packet,
//	    server_port, my_port,
//	    TCP_FLAG_ACK_V,
//	    0, 0, 0, 0,
//	    server_mac, server_ip
//	    );
//	    time_wait_counter = TIME_WAIT_TIMEOUT;
//	  }
//	  break;
//    }
  }
  not_expected_packet = false;
}

void handle_output_pck() {

  if(curr_state == IDLE && communicate_changes == true) {
    es.ES_make_arp_request(raw_packet, server_ip);
    es.ES_tcp_client_send_packet(
    raw_packet,
    server_port, my_port,
    TCP_FLAG_ACK_V,
    1, 1, 0, 0,
    server_mac, server_ip
    );
    arp_wait_counter = ARP_TIMEOUT;
    curr_state = AWAITING_ARP_REPLY;
    return;
  }

  switch(curr_state) {
  case ARP_SUCCESS:
    es.ES_tcp_client_send_packet(
    raw_packet,
    server_port, my_port,
    TCP_FLAG_SYN_V,
    1, 1, 0, 0,
    server_mac, server_ip
    );
    curr_state = AWAITING_SYNACK;
    break;
  case SYN_SUCCESS:
    codify_info_packet();
    es.ES_tcp_client_send_packet(
    raw_packet,
    server_port, my_port,
    TCP_FLAG_PUSH_V | TCP_FLAG_ACK_V,
    0, 0, 0, packet_length,
    server_mac, server_ip
    );
    curr_state = AWAITING_ACK;
    break;
  case MESSAGE_RECIEVED:
    es.ES_tcp_client_send_packet(
    raw_packet,
    server_port, my_port,
    TCP_FLAG_FIN_V,
    0, 0, 0, 0,
    server_mac, server_ip
    );
    curr_state = AWAITING_FINACK;
    communicate_changes = false;
    break;
  }
  ack_wait_counter = ACK_TIMEOUT;
}

void codify_info_packet() {
	uint8_t * aux_raw = raw_packet;

	memcpy(aux_raw, &myip, sizeof(myip));
	aux_raw += sizeof(myip);

	int sensors_qty = SENSORS_QTY;
	memcpy(aux_raw, &(sensors_qty), sizeof(int));
	aux_raw += sizeof(int);

	int i;

	for(i = 0; i < SENSORS_QTY; i++) {
		memcpy(aux_raw, (const void *)raw_packet[i], sizeof(individual_info_t));
		aux_raw += sizeof(individual_info_t);
	}
	packet_length = ((uint16_t)aux_raw) - ((uint16_t)raw_packet);
}

void handle_connection_status() {
  if(curr_state == TIME_WAIT) {
    if(time_wait_counter == 0) {
      curr_state = IDLE;
    } else {
      time_wait_counter--;
    }
  }
  if(curr_state == AWAITING_ARP_REPLY) {
    if(arp_wait_counter == 0) {
      curr_state = IDLE;
    } else {
      arp_wait_counter--;
    }
  }
  if(curr_state == AWAITING_ACK || curr_state == AWAITING_SYNACK
    || curr_state == AWAITING_FIN || curr_state == AWAITING_FINACK) {
    if(ack_wait_counter == 0) {
      curr_state = IDLE;
    } else {
      ack_wait_counter--;
    }
  }
}
