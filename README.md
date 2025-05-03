# chat-Application-Using-Cpp
Overview:-
This project is a TCP-based terminal chat application written in C++ using the Winsock2 API, which allows multiple clients to connect to a central server and exchange text messages in real-time. The server handles multiple clients via multithreading, broadcasting each client's message to others. The client enables real-time input/output using separate threads for sending and receiving.

KEY COMPONENTS
🖥️ 1. Server (chat server)
Uses Winsock2 for TCP communication.
Maintains a list of active client sockets.
Accepts new client connections and spawns a thread for each.
Forwards received messages to all other connected clients.
Handles client disconnects cleanly.

🧑‍💻 2. Client (chat client)
Connects to the server using TCP.
Sends user messages prefixed with a username.
Receives and displays messages from other clients.
Uses two threads:
One for sending typed messages.
One for receiving incoming messages.

🧵 3. Multithreading
std::thread is used for concurrent send/receive on the client side.
The server also uses threads to handle multiple clients concurrently.

🔐 4. Synchronization
std::mutex ensures thread-safe operations on shared resources like the client list.

