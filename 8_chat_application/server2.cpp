#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <chrono>

int main(){

// Start the clock
  auto start_time = std::chrono::high_resolution_clock::now();
  
  bool timer = false;
  int server_fd, new_socket;
  int opt = 1;
  struct sockaddr_in address;
  char buffer[1024] = {0};
  socklen_t addrlen = sizeof(address);

  if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0){
    perror("Socket Failed");
    exit(EXIT_FAILURE);
  }
  
  perror("Creating Socket");

  if (timer == true){
    // Stop the clock
    auto end_time1 = std::chrono::high_resolution_clock::now();

    // Calculate the duration in milliseconds
    auto duration1 = std::chrono::duration_cast<std::chrono::milliseconds>(end_time1 - start_time);
    // Output the duration
    std::cout << "Execution time: " << duration1.count() << " milliseconds" << std::endl;
  }
 
  if (setsockopt(server_fd, SOL_SOCKET,SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))){
    perror("Setsockopt");
    exit(EXIT_FAILURE);
  }

  perror("setsockopt");

  if (timer == true){
    // Stop the clock
    auto end_time2 = std::chrono::high_resolution_clock::now();

    // Calculate the duration in milliseconds
    auto duration2 = std::chrono::duration_cast<std::chrono::milliseconds>(end_time2 - start_time);
    // Output the duration
    std::cout << "Execution time: " << duration2.count() << " milliseconds" << std::endl;
  }

  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(8080);

  if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0){
    perror("Bind Failed");
    exit(EXIT_FAILURE);
  }
  
  perror("Binding port");

  if (timer == true){
    // Stop the clock
    auto end_time3 = std::chrono::high_resolution_clock::now();

    // Calculate the duration in milliseconds
    auto duration3 = std::chrono::duration_cast<std::chrono::milliseconds>(end_time3 - start_time);
    // Output the duration
    std::cout << "Execution time: " << duration3.count() << " milliseconds" << std::endl;
  }

  if (listen(server_fd, 3) < 0){
  
    perror("Listen Failed");
    exit(EXIT_FAILURE);
  }

  perror("Listen");
  if (timer == true){
    // Stop the clock
    auto end_time4 = std::chrono::high_resolution_clock::now();

    // Calculate the duration in milliseconds
    auto duration4 = std::chrono::duration_cast<std::chrono::milliseconds>(end_time4 - start_time);
    // Output the duration
    std::cout << "Execution time: " << duration4.count() << " milliseconds" << std::endl;
  }

  std::cout << "SERVER IS LIVED!" << std::endl;

  if ((new_socket = accept(server_fd, (struct sockaddr*)&address, &addrlen)) < 0){
    perror("Accept error");
    exit(EXIT_FAILURE);
  }

  perror("Accept Client");

  if (timer == true){
    // Stop the clock
    auto end_time5 = std::chrono::high_resolution_clock::now();

    // Calculate the duration in milliseconds
    auto duration5 = std::chrono::duration_cast<std::chrono::milliseconds>(end_time5 - start_time);
    // Output the duration
    std::cout << "Execution time: " << duration5.count() << " milliseconds" << std::endl;
  }

  while(true){
    memset(buffer, 0, sizeof(buffer));
    int bytes_read = read(new_socket, buffer, sizeof(buffer));
    if (bytes_read == 0){
      std::cout << "Client disconnected" << std::endl;
      break;
    }

    std::cout << "Client: " << buffer << std::endl;

    send(new_socket, buffer, strlen(buffer), 0);

    if (strcmp(buffer, "exit") == 0){
      std::cout << "Exit command received. Closing connection." << std::endl;
      break;
    }
  }

  close(new_socket);
  close(server_fd);
  return 0;

}
