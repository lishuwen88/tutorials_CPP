#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>

//using namespace std;

int main()
{
	// Create a socket
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1)
	{
		return 1;
	}


	// Create a hint structure for the server we're connecting with
	int port = 54000;
	std::string ipAddress = "127.0.0.1";

	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

	// Connect to the server on the socket
	int connectRes = connect(sock, (sockaddr*)&hint, sizeof(hint));
	if (connectRes == -1)
	{
		return 1;
	}


	// while Loop:
	char buf[4096];
	std::string userInput;

	do {

		// Enter lines of text
		std::cout << "> ";
		getline(std::cin, userInput);
		
		// Send to server
		int sendRes = send(sock, userInput.c_str(), userInput.size() + 1.0, 0);
		
		// Check if failed
		if (sendRes == -1)
		{
			std::cout << "Could not send to server! Whoops!\r\n";
			continue;
		}

		// Wait for response
		memset(buf, 0, 4096);
		int bytesReceived = recv(sock, buf, 4096, 0);
		// prevent crash when error
		if (bytesReceived == -1)
		{
			std::cout << "There was an error getting resonse from server \r\n";
		}
		else
		{
			// Display response
			std::cout << "SERVER> " << std::string(buf, bytesReceived) << "\r\n";
		}
	} while (true);
	// Close the socket
	close(sock);


	return 0;
}