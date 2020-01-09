#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>

#include "DTCProtocol.cpp"
//#include "DTCProtocol.h"

//using namespace std;

struct Header{
		u_int16_t size;
		u_int16_t type;
	};


int main()
{
	// Create a socket
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1)
	{
		return 1;
	}


	// Create a hint structure for the server we're connecting with
	// ("127.0.0.1", 11099)
	int port = 11099;
	std::string ipAddress = "192.168.1.100";
	//std::string ipAddress = "127.0.0.1";

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
	char buf[1024];
	//std::string userInput;

	//do {

	// Enter lines of text
	// std::cout << "> ";
	// getline(std::cin, userInput);
	
	// Encoding Request
	DTC::s_EncodingRequest enc_req;
	
	// Send to server
	char bytes2send[enc_req.Size];
	memcpy(bytes2send, &enc_req, enc_req.Size);
	int sendRes = send(sock, bytes2send, enc_req.Size, 0);
	
	// Check if failed
	if (sendRes == -1)
	{
		std::cout << "Could not send to server! Whoops!\r\n";
		//continue;
	}

	// Wait for response
	DTC::s_EncodingResponse enc_resp;
	Header header;

	memset(buf, 0, 4);
	//int bytesReceived = recv(sock, buf, 4, 0);
	int bytesReceived = recv(sock, buf, 4, 0);
	memcpy(&header, static_cast<void*>(buf), 4);	
	// prevent crash when error
	if (bytesReceived == -1)
	{
		std::cout << "There was an error getting resonse from server \r\n";
	}
	else
	{
		// Display response
		//std::cout << "SERVER> " << std::string(buf, bytesReceived) << "\r\n";
		
		// Get rest of message
		//DTC::s_EncodingResponse enc_resp;
		u_int16_t m_size = header.size - 4;
		std::cout << "  m_size: " << m_size << std::endl;
		memset(buf + 4, 0, m_size);
		int bytesReceived = recv(sock, buf+4, m_size, 0);
		//memcpy(&enc_resp, bytesReceived, header.size);
		
		// combine header and message into 1 byte array

		enc_resp.CopyFrom(static_cast<void*>(buf));
		std::cout << "Enc_Resp: Size " << enc_resp.Size << std::endl;
		std::cout << "Enc_Resp: Type " << enc_resp.Type << std::endl;
		std::cout << "Enc_Resp: ProtocolVersion " << enc_resp.ProtocolVersion << std::endl;
		std::cout << "Enc_Resp: Encoding " << enc_resp.Encoding << std::endl;
		std::cout << "Enc_Resp: ProtocolType " << enc_resp.ProtocolType << std::endl;

	}
	
	// Logon request
	int HRTBT = 24;
	DTC::s_LogonRequest logon_req;
	logon_req.SetClientName("GOGOGOMEZZZZZ");
	logon_req.HeartbeatIntervalInSeconds = HRTBT;
	
	// Send to server
	char bytes2send2[logon_req.Size];
	memcpy(bytes2send2, &logon_req, logon_req.Size);
	int sendlogon = send(sock, bytes2send2, logon_req.Size, 0);
	
	// Check if failed
	if (sendlogon == -1)
	{
		std::cout << "Could not send to server! Whoops!\r\n";
		//continue;
	}

	// Wait for response
	DTC::s_LogonResponse logon_resp;
	//Header header; // already initialized above

	memset(buf, 0, 4);
	//int bytesReceived = recv(sock, buf, 4, 0);
	bytesReceived = recv(sock, buf, 4, 0);
	memcpy(&header, static_cast<void*>(buf), 4);	
	// prevent crash when error
	if (bytesReceived == -1)
	{
		std::cout << "There was an error getting resonse from server \r\n";
	}
	else
	{
		// Display response
		//std::cout << "SERVER> " << std::string(buf, bytesReceived) << "\r\n";
		
		// Get rest of message
		//DTC::s_LogonResponse logon_resp;
		u_int16_t m_size = header.size - 4;
		std::cout << "  m_size: " << m_size << std::endl;
		memset(buf + 4, 0, m_size);
		int bytesReceived = recv(sock, buf+4, m_size, 0);
		//memcpy(&enc_resp, bytesReceived, header.size);
		
		// combine header and message into 1 byte array

		logon_resp.CopyFrom(static_cast<void*>(buf));
		std::cout << "Logon_Resp: Size: " << logon_resp.Size << std::endl;
		std::cout << "Logon_Resp: Type: " << logon_resp.Type << std::endl;
		std::cout << "Logon_Resp: ProtocolVersion: " << logon_resp.ProtocolVersion << std::endl;
		std::cout << "Logon_Resp: Result: " << logon_resp.GetResult() << std::endl;
		std::cout << "Logon_Resp: Resultdirect: " << logon_resp.Result << std::endl;
		std::cout << "Logon_Resp: Resulttext: " << logon_resp.GetResultText() << std::endl;
		
		std::cout << "Logon_Resp: Resulttext direct: " << logon_resp.ResultText << std::endl;
		std::cout << "Logon_Resp: ReconnectAddress: " << logon_resp.ReconnectAddress << std::endl;
		std::cout << "Logon_Resp: integer1: " << logon_resp.Integer_1 << std::endl;
		std::cout << "Logon_Resp: Servername: " << logon_resp.ServerName << std::endl;
		std::cout << "Logon_Resp: Mktdepthupdateblable: " << logon_resp.MarketDepthUpdatesBestBidAndAsk << std::endl;
		std::cout << "Logon_Resp: TradingIsSupported: " << logon_resp.TradingIsSupported << std::endl;
		std::cout << "Logon_Resp: OCOsupported: " << logon_resp.OCOOrdersSupported << std::endl;
		std::cout << "Logon_Resp: OrderCancelReplaceSuppported: " << logon_resp.OrderCancelReplaceSupported << std::endl;
		std::cout << "Logon_Resp: SymbolExchangeDelimiteder: " << logon_resp.SymbolExchangeDelimiter << std::endl;
		std::cout << "Logon_Resp: SecurityDefSupported: " << logon_resp.SecurityDefinitionsSupported << std::endl;
		std::cout << "Logon_Resp: HistoricalPriceDataSupported: " << logon_resp.HistoricalPriceDataSupported << std::endl;
		std::cout << "Logon_Resp: ResubscribeWhenMarketDataFeedAvailable " << logon_resp.ResubscribeWhenMarketDataFeedAvailable << std::endl;
		std::cout << "Logon_Resp: MarketDepthIsSupported " << logon_resp.MarketDepthIsSupported << std::endl;
		std::cout << "Logon_Resp: OneHistoricalPriceDatablabla " << logon_resp.OneHistoricalPriceDataRequestPerConnection << std::endl;
		std::cout << "Logon_Resp: BracketSupported " << logon_resp.BracketOrdersSupported << std::endl;
		std::cout << "Logon_Resp: UseIntegerPriceOrderMsg " << logon_resp.UseIntegerPriceOrderMessages << std::endl;
		std::cout << "Logon_Resp: UsesMultiplePos-SymNacc " << logon_resp.UsesMultiplePositionsPerSymbolAndTradeAccount << std::endl;
		std::cout << "Logon_Resp: MarketDataSupported: " << logon_resp.MarketDataSupported << std::endl;

	}

	// secdef?
	//} while (true);
	// Close the socket
	close(sock);


	return 0;
}
