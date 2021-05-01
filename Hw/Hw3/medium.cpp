class Medium
{
public:
    Medium(string name) { m_name = name; }
    string id() const { return m_name; }
    virtual string connect() const = 0;
    virtual string transmit(string msg) const { return "text: " + msg; }
    virtual ~Medium() {}
private:
    string m_name;
};

class TwitterAccount : public Medium
{
public:
    TwitterAccount(string name) : Medium(name) {}
    virtual string connect() const { return "Tweet"; };
    virtual ~TwitterAccount() { cout << "Destroying the Twitter account " + this->id() + "." << endl; }
};

class Phone : public Medium
{
public:
    Phone(string name, CallType way) : Medium(name), m_way(way) {}
    virtual string connect() const { return "Call"; }
    virtual string transmit(string msg) const;
    virtual ~Phone() { cout << "Destroying the phone " + this->id() + "." << endl; }
private:
    CallType m_way;
};

string Phone::transmit(string msg) const
{
    string sendWay;

    if (m_way == VOICE) {
        sendWay = "voice: ";
    }
    else {
        sendWay = "text: ";
    }

    return sendWay + msg;
}

class EmailAccount : public Medium
{
public:
    EmailAccount(string name) : Medium(name) {}
    virtual string connect() const { return "Email"; }
    virtual ~EmailAccount() { cout << "Destroying the email account " + this->id() + "." << endl; }
};