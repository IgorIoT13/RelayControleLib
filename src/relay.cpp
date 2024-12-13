#include "relay.h"


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
    this->enableWork = true;
    pinMode(this->pinRelay, OUTPUT);
    pinMode(this->pinLed, OUTPUT);

    digitalWrite(this->pinRelay, LOW);
    digitalWrite(this->pinLed, LOW);

    this->setOnFunc(nullptr);
    this->setOffFunc(nullptr);


    return ALL_OK;

}

        /**
         * ----------------------------------------------------------------------------------------------------------------
         * --------------------------- Manual contole state ---------------------------------------------------------------
         * ----------------------------------------------------------------------------------------------------------------
         */

ErrorList Relay::offRelay(){
    ErrorList err = this->checkValues();
    if(err == ALL_OK){
        this->status = false;
        digitalWrite(this->pinLed, LOW);
        digitalWrite(this->pinRelay, LOW);

        if(this->func_OFF != nullptr){
            this->func_OFF();
        }
    }

    return err;
}


ErrorList Relay::onRelay(){
    ErrorList err = this->checkValues();
    if(err == ALL_OK && this->enableWork){
        this->status = true;
        digitalWrite(this->pinLed, HIGH);
        digitalWrite(this->pinRelay, HIGH);

        if(this->func_ON != nullptr){
            this->func_ON();
        }
    }
    return err;
}

ErrorList Relay::disable(){
    this->enableWork = false;
    this->offState();
}


ErrorList Relay::enable(){
    this->enableWork = true;
}

    /**
     * ----------------------------------------------------------------------------------------------------------------
     * --------------------------- Automatic controle -----------------------------------------------------------------
     * ----------------------------------------------------------------------------------------------------------------
     */


bool Relay::changeState(){
    if(this->status){
        this->status = false;
    }else{
        this->status = true;
    }
    return this->status;
}


ErrorList Relay::offState(){
    ErrorList err = this->checkValues();
    if(err == ALL_OK){
        this->status = false;
    }
    
    return err;
}

ErrorList Relay::onState(){
    ErrorList err = this->checkValues();
    if(err == ALL_OK){
        this->status = true;
    }
    return err;
}


ErrorList Relay::tick(){

    if(status){
        if(this->status != digitalRead(this->pinRelay)) this->onRelay();
    }else{
        if(this->status != digitalRead(this->pinRelay)) this->offRelay();
    }

    return ALL_OK;
 }


    /**
     * ----------------------------------------------------------------------------------------------------------------
     * --------------------------- Setters ----------------------------------------------------------------------------
     * ----------------------------------------------------------------------------------------------------------------
     */


 ErrorList Relay::setName(String newName){
    ErrorList err = this->checkName(newName);
    if(err == ALL_OK){
        this->name = newName;
    }
    return err;
 }

 ErrorList Relay::setRelayPin(uint8_t newPinRelay){
    ErrorList err = this->checkPin(newPinRelay);
    if(err == ALL_OK){
        this->pinRelay = newPinRelay;
    }
    return err;
 }

 ErrorList Relay::setLedPin(uint8_t newPinLed){
    ErrorList err = this->checkPin(newPinLed);
    if(err == ALL_OK){
        this->pinLed = newPinLed;
    }
    return err;
 }


void Relay::setOnFunc(void(*onFunc)(void)){
    if(onFunc != nullptr){
        this->func_ON = onFunc;
    }else{
        this->func_ON = nullptr;
    }
    
}

void Relay::setOffFunc(void (*offFunc)(void)){
    if(offFunc != nullptr){
        this->func_OFF = offFunc;
    }else{
        this->func_OFF = nullptr;
    }
}

    /**
     * ----------------------------------------------------------------------------------------------------------------
     * --------------------------- Getters ----------------------------------------------------------------------------
     * ----------------------------------------------------------------------------------------------------------------
     */

 uint8_t Relay::getRelayPin(){
    return this->pinRelay;
 }
 uint8_t Relay::getLedPin(){
    return this->pinLed;
 }
 String Relay::getRelayName(){
    return this->name;
 }

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


