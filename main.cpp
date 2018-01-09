#include "kobot.h"

int main(int argc, char *argv[])
{
	Uart_open() ; // 통신 준비
	Init_console() ; 

	usleep(1000000) ;
	Check_remote() ;

    std::cout << " start " << std::endl ;
    hockey_passer();
	Uart_close() ;
	return 0;
}
