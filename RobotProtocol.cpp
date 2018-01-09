#include "RobotProtocol.h"

struct termios options;
int uart0_filestream  = -1;
unsigned char read_value;

void Uart_open(void){
	
                uart0_filestream = open("/dev/ttyAMA0", O_RDWR | O_NOCTTY | O_NDELAY);          //Open in non blocking re$
                if (uart0_filestream == -1) {
                        //ERROR - CAN'T OPEN SERIAL PORT
                        printf("Error - Unable to open UART.  Ensure it is not in use by another application\n");
                }
}


void  Init_console(void){
	 tcgetattr(uart0_filestream, &options);
       	 options.c_cflag = B4800 | CS8 | CLOCAL | CREAD;         //<Set baud rate
       	 options.c_iflag = IGNPAR;
       	 options.c_oflag = 0;
       	 options.c_lflag = 0;
       	 tcflush(uart0_filestream, TCIFLUSH);
       	 tcsetattr(uart0_filestream, TCSANOW, &options);
}

void Motion(unsigned char move_value){

	 if (uart0_filestream != -1){                                       //      &tx_buffer[0] , (p_tx_buffer - &tx_buffer[0])
                int count = write(uart0_filestream,&move_value, 1 );           //Filestream, bytes to write, number of bytes to $
                if (count < 0) {
                        printf("UART TX error\n");
                }
	Check_Read() ;
	}        
}

void Motion2(unsigned char move_value){
	//std::cout<<"MOTION++++++++++"<<(int)move_value<<std::endl;
	if(uart0_filestream != -1){
		int count=write(uart0_filestream, &move_value, 1);
		if(count<0){
			printf("UART TX error\n");
		}
	Check_Read2();
	}
}

void Uart_close(void){
	close(uart0_filestream);
}


unsigned char Check_Read(){

	int count = 0;
	int read_length = -1;
	std::cout << "Check Read!" << std::endl ; 
//	do{
//		read_length = read(uart0_filestream , &read_value, 1);
//	}while(read_value == 'Z');
	std::cout << read_value<<std::endl;
	std::cout << "ack" << std::endl ; 
	read_value = 0;
	return read_value;
}
unsigned char Check_Read2(){
	int count=0;
	int read_length=-1;
//	std::cout<<"Check Read!"<<std::endl;
	do{
		read_length=read(uart0_filestream, &read_value,1);
	}while(read_value!='Z');
//	std::cout<<read_value<<std::endl;
//	std::cout<<"ack"<<std::endl;
	read_value=0;
	return read_value;
}

unsigned char Check_remote(){
	int count = 0;
	int read_length = -1;
	std::cout << "Check Remote!" << std::endl ; 
	//do{
	//	read_length = read(uart0_filestream , &read_value, 1);
	//}while(read_value != 'a');
	std::cout << read_value<<std::endl;
	std::cout << "ack" << std::endl ; 
	read_value = 0;
	return read_value;
}
	
void ProcessMotion(unsigned char move_value)
{
	Motion(move_value) ;
	switch(move_value){
		case 100 : usleep(800000) ; break ;//전진달리기50
		case 101 : usleep(2000000) ; break ;//연속전진
		case 102 : usleep(2500000) ; break ;//연속후진
		case 103 : usleep(1500000) ; break ;//왼쪽옆으로20
		case 104 : usleep(1500000) ; break ;//오른쪽옆으로20
		case 105 : usleep(3000000) ; break ;
		case 106 : usleep(1500000) ; break ; 
		case 107 : usleep(1800000) ; break ;
		case 108 : usleep(1800000) ; break ;

		case 200 : usleep(1000000) ; break; //공들기
		case 201 : usleep(2000000) ; break; //공들고연속전진
		case 202 : usleep(1000000) ; break; //공들고전진천천히한걸음
		case 203 : usleep(2000000) ; break; //공들고연속후진
		case 204 : usleep(1500000) ; break; //공들고후진천천히한걸음
		case 205 : usleep(500000) ; break;  // 공들고 오른쪽 옆으로 20
		case 206 : usleep(500000) ; break; //공들고 왼쪽 옆으로 20
		case 207 : usleep(500000) ; break; //공들고 오른쪽 턴 10
		case 208 : usleep(500000) ; break; //공들고 왼쪽 턴 10
		case 209 : usleep(500000) ; break; //공들고 오른쪽 턴 20
		case 210 : usleep(500000) ; break; //공들고 왼쪽 턴 20
		case 211 : usleep(5000000) ; break; //공넣기
		case 212 : usleep(500000) ; break; //공찾기고개
		case 213 : usleep(500000) ; break; //기본고개
		case 214 : usleep(1000000); break;
		case 215 : usleep(1000000); break;
    }
}
