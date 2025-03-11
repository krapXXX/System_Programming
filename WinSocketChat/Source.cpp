#include <iostream>
#include<string>
#include "Socket.h"

using namespace std;

bool isDigit(char c)
{
	char digits[] = "0123456789";
	for (int i = 0; i < 10; i++)
	{
		if (c == digits[i])
			return true;
	}
	return false;
}


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int nChoice;
	int port = 24242;
	string ipAddress = "127.0.0.1";
	int price[3] = { 7, 5, 12 };
	int total = 0;
	char receiveMessage[MAXSTRLEN];
	char sendMessage[MAXSTRLEN];

	cout << "1) Start server" << endl;
	cout << "2) Connect to server" << endl;
	cout << "3) Exit" << endl;
	cin >> nChoice;
    if (nChoice == 1)
    {
        ServerSocket server;
        cout << "Starting server..." << endl;
        server.StartHosting(port);

        while (true)
        {
            cout << "\tWaiting..." << endl;
            server.ReceiveData(receiveMessage, MAXSTRLEN);
            cout << "Received: " << receiveMessage << endl;

            string Menu = "\n1. Fries - 7$\n2. Soda - 5$\n3. Ice-Cream - 12$\n";
            if (strcmp(receiveMessage, "Menu") == 0)
            {
                server.SendDataMessage(Menu.c_str());
            }
            else if (strcmp(receiveMessage, "Menu") != 0)
            {
                bool foundFirst = false;
                int amountIndex = 0;
                int index = -1;
                char amount[100];
                int i = 0;
                total = 0; 
                int temp;

                while (receiveMessage[i] != '\0')
                {
                    if (isDigit(receiveMessage[i]))
                    {
                        if (!foundFirst)
                        {
                            index = receiveMessage[i] - '0'; 
                            foundFirst = true;
                        }
                        else
                        {
                            temp = i;
                            for (int j = i; j < receiveMessage[i] != '\0'; j++)
                            {
								if (isDigit(receiveMessage[temp]))
								{
									amount[amountIndex] = receiveMessage[temp];
                                    amountIndex++;
                                    temp++;
								}
                            }
                        }
                    }

                    if (index >= 0 && index <= 3 && amountIndex > 0)
                    {
                        int cost = price[index - 1] * stoi(amount); 
                        total += cost; 
                        foundFirst = false; 
                        amountIndex = 0; 
                        memset(amount, 0, sizeof(amount)); 

                        while (receiveMessage[i] != '\0' && !isDigit(receiveMessage[i]))
                        {
                            i++;
                        }
                    }
                    i++; 
                }

                string response = "Total: " + to_string(total) + "$";
                server.SendDataMessage(response.c_str());

                if (strcmp(receiveMessage, "end") == 0)
                    break;
            }
        }
    }

	else if (nChoice == 2)
	{
		cout << "IP address = 127.0.0.1 " << endl;

		ClientSocket client;
		client.ConnectToServer(ipAddress.c_str(), port);
		while (true)
		{
			char buff[100];
			cin.ignore();
			cin.get(buff, 100);

			client.SendDataMessage(buff);

			cout << "\tWaiting" << endl;

			client.ReceiveData(receiveMessage, MAXSTRLEN);
			cout << "Received: " << receiveMessage << endl;

			if (strcmp(receiveMessage, "end") == 0 ||
				strcmp(sendMessage, "end") == 0)
				break;
		}
		client.CloseConnection();
	}
	else if (nChoice == 3)
		return 0;
}



