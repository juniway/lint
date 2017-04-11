// isIpLeagal

// 要点
// 1. 
// 2.

bool valid_digit(char *ip_str){ 
	char *p = ip_str;
    while (*p) { 
        if (*p >= '0' && *p <= '9') 
            ++p;
        else 
            return false;
    } 
    return atoi(p) >= 0 && atoi(p) <= 255;
} 
    
/* return 1 if IP string is valid, else return 0 */ 
bool is_valid_ip(char *ip_str){ 
    int dots = 0; 
    char *ptr; 
    if (ip_str == nullptr) 
        return false; 
    
    ptr = strtok(ip_str, DELIM); // get the first part
    if (ptr == nullptr)
        return false; 
    
    while(ptr){
        // after parsing string, it must contain only digits
        if (!valid_digit(ptr)) return false; 
        // parse remaining string
        ptr = strtok(nullptr, DELIM); 
        if (ptr != nullptr)
            ++dots;
    }
    // valid IP string must contain 3 dots
    if (dots != 3) 
        return false; 
    return true; 
}

// 直接用库函数判断
if (INADDR_NONE == inet_addr(AsciiBuff)) return true;
else return false;


// strtok()
int main (){
	char str[] ="- This, a sample string.";
	char * pch;
	printf ("Splitting string \"%s\" into tokens:\n",str);
	pch = strtok (str," ,.-");
	while (pch != NULL){
		printf ("%s\n",pch);
		pch = strtok (NULL, " ,.-");
	}
	return 0;
}

Output:
Splitting string "- This, a sample string." into tokens:
This
a
sample
string