#include <iostream>
using namespace std;


/*
Implementujte třídu KeyValue dle přednášky a vytvořte zřetězenou
lineární strukturu mnoha (např. tisíce) objektů a pracujte s ní (vypište
např. všechny klíče od prvního do posledního objektu).
*/

class KeyValue
{
    private:
        int key;
        double value;
        KeyValue *next;
    
    public:
        KeyValue(int k, double v);
        ~KeyValue();
        int GetKey();
        double GetValue();
        KeyValue* GetNext();
        KeyValue* CreateNext(int k, double v);
};


KeyValue :: KeyValue(int k, double v)
{
    this->key = k;
    this->value = v;
    this->next = nullptr;
}

KeyValue::~KeyValue()
{
    if (this->next != nullptr)
    {
        delete this->next;
        this->next = nullptr;
        cout << ".";
    }
}

int KeyValue::GetKey()
{
    return this->key;
}

double KeyValue::GetValue()
{
    return this->value;
}

KeyValue* KeyValue::GetNext()
{
    return this->next;
}

KeyValue* KeyValue::CreateNext(int k, double v)
{
    this-> next = new KeyValue(k,v);
    return this->next;
}

int main()
{   /*
    KeyValue *kv1 = new KeyValue(1,1.5);
    cout << kv1->CreateNext(2,2.5)->GetKey() << endl;
    //cout << kv1->GetNext() << endl;

    KeyValue *kv2 = kv1->GetNext();
    //cout << kv2->GetValue() << endl;
    cout << kv2->GetNext() << endl;

    delete kv1;
    kv1 = nullptr;
    kv2 = nullptr;
    */

    int i = 1;
    int len = 1000;
    KeyValue* listOfKeyValues [len];

    listOfKeyValues[0] = new KeyValue(0, 0.5);
    cout << listOfKeyValues[0]->GetKey() << " ";
    while (i < len){
        listOfKeyValues[i] = listOfKeyValues[i-1]->CreateNext(i, i+0.5);
        cout << listOfKeyValues[i]->GetKey() << " ";
        i++;
    }
    cout<< endl;

    delete listOfKeyValues[0];
    cout<<endl;
    for (int i = 0; i < len; i++){
        listOfKeyValues[i] = nullptr;
    }

    //cout << kv1->GetKey() << endl;
    //cout << kv2->GetKey()  << endl;

    //getchar();
    return 0;
}