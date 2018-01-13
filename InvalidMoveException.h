#ifndef InvalidMoveException_h
#define InvalidMoveException_h

class InvalidMoveException {
    std::string name;
public:
    InvalidMoveException(std::string name) : name{name} {}
    void prettyprint() {
        std::cout << "Invalid move: " << name << std::endl;
    }
};

#endif /* InvalidMoveException_h */
