void toUpperCase(std::string &str) { //ERROR: Incomplete type "void" is not allowedC/C++(70)
    for (char &c : str) {
        if (c >= 'a' && c <= 'z') {
            c = c - 'a' + 'A';
        }
    }
}