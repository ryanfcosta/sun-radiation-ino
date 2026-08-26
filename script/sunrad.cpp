/*
#include <iostream>
#include <string>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <curl/curl.h>

int iniciarSerial(const char* porta){
    int fd = open(porta, O_RDWR | O_NOCTTY | O_NDELAY);
    if(fd == -1) return -1;
    
    struct termios tty;
    tcgetattr(fd, &tty);
    cfsetispeed(&tty, B9600);
    cfsetospeed(&tty, B9600);
    tty.c_cflag |= (CLOCAL | CREAD);
    tty.c_cflag &= ~PARENB;
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;
    tty.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    tcsetattr(fd, TCSANOW, &tty);
    return fd;

}

size_t writeCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

bool checkAlerta(){
    CURL *curl = curl_easy_init();
    std::string buffer;

    if(curl){
        curl_easy_setopt(curl, CURLOPT_URL, "https://services.swpc.noaa.gov/products/noaa-scales.json");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "AnalySinoSolar/1.0");
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
    if (buffer.find("\"G\":\"0\"") != std::string::npos && 
        buffer.find("\"S\":\"0\"") != std::string::npos && 
        buffer.find("\"R\":\"0\"") != std::string::npos) {
        return false;
    }
    return true;
}

int main(){
    const char* porta = "/dev/ttyACM1";
    int serial_fd = iniciarSerial(porta);

    if(serial_fd < 0){
        std::cerr << "ERRO CONEXÃO COM ARDUINO EM " << porta << std::endl; 
        return 1;
    }

    std::cout << "ANALISANDO ATIVIDADE SOLAR\n";

    while(true){
        bool alerta = checkAlerta();

        if(alerta){
            std::cout << "RADIAÇÃO ELEVADA\n";
            write(serial_fd, "R", 1);
        }else {
            std::cout << "SOL CALMO\n";
            write(serial_fd, "G", 1);
        }
        sleep(10);
    }
    close(serial_fd);
    return 0;
}
*/