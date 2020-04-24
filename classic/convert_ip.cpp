 #include <stdio.h>
 #include <stdint.h>

 // char ipAddressString[16] = "192.168.125.5";
 char ipAddressString[16] = "218.30.116.7";
 char netMaskString[16] = "255.255.0.0";
 char subnetString[16] = "192.168.0.0";


// %u (uint) %uh (uint16_t), %uhh (uint8_t)
// hh 和整数转换说明符一起使用，表示一个signed char 或者unsigned char类型数值。
// 示例：“%hhu”、“%hhx”和“%6.4hhd”
// 参考：http://my.oschina.net/jinzei/blog/98699

 uint32_t parseIPV4string(char* ipAddress) {
   char ipbytes[4];
   sscanf(ipAddress, "%uhh.%uhh.%uhh.%uhh", &ipbytes[3], &ipbytes[2], &ipbytes[1], &ipbytes[0]);
   printf("1:%c,2:%c,3%c,4:%c\n", ipbytes[0], ipbytes[1], ipbytes[2], ipbytes[3]);
   return ipbytes[0] | ipbytes[1] << 8 | ipbytes[2] << 16 | ipbytes[3] << 24;
 }

 int main(){

     uint32_t ipAddress = parseIPV4string(ipAddressString);
     uint32_t netmask = parseIPV4string(netMaskString);
     uint32_t subnet = parseIPV4string(subnetString);
     printf("ipAddress: %u\n", ipAddress);
     printf("netmask: %u\n", netmask);
     printf("subnet: %u\n", subnet);

     if((ipAddress & netmask) == subnet) {
         printf("true\n");
         return 0;
     }
     printf("false\n");
 }
