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

    return ALL_OK;

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

    return ALL_OK;
}

ErrorList Relay::onRelay(){
    ErrorList err = this->checkValues();
    if(err != ALL_OK){
        return err;
    }

    return ALL_OK;
}


 ErrorList Relay::tick(){

    return ALL_OK;
 }




 ErrorList Relay::setName(String newName){}

 ErrorList Relay::setRelayPin(uint8_t newPinRelay){}

 ErrorList Relay::setLedPin(uint8_t newPinLed){}

 uint8_t Relay::getRelayPin(){}
 uint8_t Relay::getLedPin(){}
 String Relay::getRelayName(){}

    /**
     * ----------------------------------------------------------------------------------------------------------------
     * --------------------------- Objectc values checkers ------------------------------------------------------------
     * ----------------------------------------------------------------------------------------------------------------
     */

 ErrorList Relay::checkValues(){
    if(this->name && this->pinRelay && this->pinLed){
        return this->checkAllValues(this->name, this->pinRelay, this->pinLed);
    }else{
        return ERR_NULL_VALUER;
    }
    
 }



ErrorList Relay::checkObjectPinRelay(){ 
    if(this->pinRelay){
        return this->checkPin(this->pinRelay);
    }else{
        return ERR_NULL_VALUER;
    }
}

ErrorList Relay::checkObjectPinLed(){
    if(this->pinLed){
        return this->checkPin(this->pinLed);
    }else{
        return ERR_NULL_VALUER;
    }
}

ErrorList Relay::checkObjectName(){
    if(this->name){
        return this->checkName(this->name);
    }else{
        return ERR_NULL_VALUER;
    }
}


    /**
     * ----------------------------------------------------------------------------------------------------------------
     * --------------------------- External values checkers -----------------------------------------------------------
     * ----------------------------------------------------------------------------------------------------------------
     */

ErrorList Relay::checkPin(uint8_t pin){
    if(pin > 40){
        return ERR_VALUER_UNCORECT;
    }
    return ALL_OK;
}


ErrorList Relay::checkName(String name){
    if(!name || name == "" || name == " "){
        return ERR_VALUER_EMPTY;
    }
    return ALL_OK;
}
ErrorList Relay::checkAllValues(String name, uint8_t pinRelay, uint8_t pinLed){
    if(this->checkPin(pinRelay) != ALL_OK){
        return this->checkPin(pinRelay);
    }else if(this->checkPin(pinLed) != ALL_OK){
        return this->checkPin(pinLed);
    }else if(this->checkName(name) != ALL_OK){
        return this->checkName(name);
    }else{
        return ALL_OK;
    }
}


