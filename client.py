import socket
import json

# Connection Constants
SERVER_IP = "127.0.0.1"
SERVER_PORT = 12345
MAX_LEN = 1024

DATA_LEN_IN_BYTES = 4
BIN_BASE = 2
DECIMAL_BASE = 10
SIZE_OF_BYTE = 8

SUCCESS_CODE = "1"

""" ****** SOCKET RELATED ****** """


def make_socket():
    print("connecting...")
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.connect((SERVER_IP, SERVER_PORT))
    return sock


def send_information(sock, msg):
    print("send msg: ", msg)
    sock.sendall(msg.encode())


def receive_response(sock):
    packet = sock.recv(MAX_LEN)
    bin_data = int(packet.decode(), BIN_BASE)
    packet = bin_data.to_bytes((bin_data.bit_length() + SIZE_OF_BYTE - 1) // SIZE_OF_BYTE, 'big').decode()
    print("SERVER: " + packet[7:])
    # Getting the result of the request from the json object
    j = json.loads(packet[7:])
    return j["status"]


""" ****** SERVER COMMUNICATION ****** """


def send_login_request(sock):
    login_req = {"username": "user1",
                 "password": "1234"}

    edit_request(sock, login_req)


def send_signup_request(sock):
    signup_req = {"username": "user1", "password": "1234", "email": "user1@gmail.com"}
    edit_request(sock, signup_req)


def edit_request(sock, json_request):
    json_request = json.dumps(json_request)  # Getting the json as a string
    json_length = str(len(json_request))
    json_length = json_length.zfill(DATA_LEN_IN_BYTES)
    # Building the packet according to the protocol
    if "email" in json.loads(json_request):
        str_packet = convert_to_binary("100") + convert_to_binary(json_length) + convert_to_binary(json_request)
    else:
        str_packet = convert_to_binary("101") + convert_to_binary(json_length) + convert_to_binary(json_request)

    send_information(sock, str_packet)


def convert_to_binary(msg):
    return ''.join(format(ord(i), 'b').zfill(SIZE_OF_BYTE) for i in msg)


""" ******* TESTS ******* """


def login(sock):
    send_login_request(sock)
    if receive_response(sock) == SUCCESS_CODE:
        print("Test passed")
    else:
        print("Test failed")


def signup(sock):
    send_signup_request(sock)
    if receive_response(sock) == SUCCESS_CODE:
        print("Test passed")
    else:
        print("Test failed")


def main():
    sock = make_socket()
    login(sock)

    sock.close()


if __name__ == "__main__":
    main()
