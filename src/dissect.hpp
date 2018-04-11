#ifndef DISSECT__hpp
#define DISSECT__hpp

inline void print_buf_chars(uint8_t * b, unsigned len) {
    printf("[%u] >|", len);
    for (int i=0; i<len; i++) {
        uint8_t c = b[i];
        if ((c >= ' ') && ((c <= '~')))
            printf(" %c|", (char)c );
        else
            printf("%02X ", c);
    }
}

inline void print_readable(uint8_t * b, unsigned len) {
    printf("[%u] >| ", len);
    for (int i=0; i<len; i++) {
        uint8_t c = b[i];
        if ((c >= ' ') && ((c <= '~')))
            printf("%c", (char)c );
    }
}

inline void print_buf_hex(uint8_t * b, unsigned len) {
    printf("[%u] > ", len);
    for (int i=0; i<len; i++) { printf("%02X ", b[i]); }
}

int dissect(const char* iface);
bool validate_iface(std::string& check_if);
void dissect_help(void);


#endif /* DISSECT__hpp */
