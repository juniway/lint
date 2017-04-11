#include<iostream>
// two ways of doing addr
//  <1>.	
	
	struct sockaddr_in server_addr;   	
	bzero(&(server_addr.sin_zero), 8);
	//bzero(&server_addr, sizeof server_addr);
	
	struct hostent *host;				
	host = gethostbyname(argv[1]);
	
	server_addr.sin_addr = *(struct sockaddr_in)host->h_addr;

//	<2>.

	struct sockaddr_in server_addr;		
	bzero(&(server_addr.sin_zero), 8);
	
	inet_pton(AF_INET, argv[1], &server_addr.sin_addr);
	


	
	