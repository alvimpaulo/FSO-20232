class Processo
{
private:
    /* data */
public:
    Processo(int startTime, int timeLeft, int priority,
             int memory,
             int printer,
             int scanner,
             int modem,
             int disk, bool isPronto);
    int timeLeft;
    int startTime;
    int priority;
    int memory;
    int printer;
    int scanner;
    int modem;
    int disk;
    bool isPronto;

    void spend1Time();
    void setProcessoIsPronto(bool newState);
};