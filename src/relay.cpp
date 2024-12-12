#include <relay.h>

Relay::Relay(String name, uint8_t pinRelay, uint8_t pinLed){
    this->init(name, pinRelay, pinLed);
}


ErrorList Relay::init(String name, uint8_t pinRelay, uint8_t pinLed){
    if(!name || name == "" || name == " "){
        return ERR_VALUER_EMPTY;
    }else if(pinRelay > 40 || pinLed > 40){
        return ERR_VALUER_UNCORECT;
    }else{
        this->name = name;
        this->pinRelay = pinRelay;
        this->pinLed = pinLed;
        return ALL_OK;
    }
}


ErrorList Relay::begin(){

    ErrorList err = this->checkValues();
    if(err != ALL_OK){
        return err;
    }


    this->status = false;
    pinMode(this->pinRelay, OUTPUT);
    pinMode(this->pinLed, OUTPUT);

    digitalWrite(this->pinRelay, LOW);
    digitalWrite(this->pinLed, LOW);

}


bool Relay::changeState(){
    if(this->status){
        this->status = false;
    }else{
        this->status = true;
    }
    return this->status;
}

ErrorList Relay::offRelay(){
    ErrorList err = this->checkValues();
    if(err != ALL_OK){
        return err;
    }

}

ErrorList Relay::onRelay(){
    ErrorList err = this->checkValues();
    if(err != ALL_OK){
        return err;
    }
}