#ifndef RELAY
#define RELAY
#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/semphr.h>

#include "defines.h"

/**
 * @version 1.0
 * @brief Class for relay 
 * 
 * @author Igor Co
 * 
 * */
class Relay{
    private:
        uint8_t pinRelay;
        uint8_t pinLed;
        String name;
        bool status;

    public:

        /**
         * 
         * @brief Constructor for relay class
         * 
         * @warning Values for the constructor cannot be empty 
         * 
         * @see Relay::init()
         * 
         * @param name Relay name (e.g., "Heat", "Fan", or "Cool").
         * @param pinRelay GPIO pin controlling the relay.
         * @param pinLed GPIO pin controlling the LED.
         * 
         */
        Relay(String name, uint8_t pinRelay, uint8_t pinLed);


        /**
         * @brief initiallization all variable and keep his ready to work
         * 
         * @return error if something do not work or init with error in another events return OK
         */
        ErrorList init(String name, uint8_t pinRelay, uint8_t pinLed);

        /**
         * 
         * @brief Setup all param and setting pin
         * 
         * @warning IF values in object is empty -do not work
         * 
         * @return error if something do not work or init with error in another events return OK
         * 
         */
        ErrorList begin();


/**
 * ____________________________________________________________________________________________________________________
 * _______________________________ Busines logic ______________________________________________________________________
 * ____________________________________________________________________________________________________________________
 */



        /**
         * ----------------------------------------------------------------------------------------------------------------
         * --------------------------- Manual contole state ---------------------------------------------------------------
         * ----------------------------------------------------------------------------------------------------------------
         */


        /**
         * @brief Toggles the relay state.
         * 
         * This function changes the relay state to its opposite value.
         * For example, if the relay is currently ON (true), it will be switched OFF (false), and vice versa.
         * 
         * @return The new state of the relay (true for ON, false for OFF).
         */
        bool changeState();


        /**
         * 
         * @brief Set state of relay false or off relay
         * 
         * @return Error list. if all okey return OK else error code
         * 
         */
        ErrorList offRelay();


        /**
         * 
         * @brief Set state of relay true or on relay
         * 
         * @return Error list. if all okey return OK else error code
         * 
         */
        ErrorList onRelay();



        /**
         * ----------------------------------------------------------------------------------------------------------------
         * --------------------------- Automatic controle -----------------------------------------------------------------
         * ----------------------------------------------------------------------------------------------------------------
         */


        /**
         * 
         * @brief Automatic check state and auto on/off relay
         * 
         * @note Use with manual contole (change, on , off) to controle relay. Need to corectly works all object.
         * 
         * @see onRelay()
         * @see offRelay()
         * @see changeState()
         * 
         * @return Error list. if all okey return OK else error code
         * 
         */
        ErrorList tick();



/**
 * ____________________________________________________________________________________________________________________
 * _______________________________ GETTERS and SETTERS ________________________________________________________________
 * ____________________________________________________________________________________________________________________
 */



    /**
     * ----------------------------------------------------------------------------------------------------------------
     * --------------------------- Setters ----------------------------------------------------------------------------
     * ----------------------------------------------------------------------------------------------------------------
     */


    /**
     * @brief Reset or set name of relay
     * 
     * @warning If name is empty don`t set this name and return ERR_VALUER_UNCORECT
     * 
     * @param newName new name for relay
     * 
     * 
     * @return Error list (if all okey return OK else error code)
     */
    ErrorList setName(String newName);


    /**
     * @brief set or reset the pin for the relay
     * 
     * @param newPinRelay new GPIO pin for relay
     * 
     * @return Error list (if all okey return OK else error code)
     */
    ErrorList setRelayPin(uint8_t newPinRelay);


    /**
     * @brief set or reset the pin for the led
     * 
     * @param newPinRelay new GPIO pin for led
     * 
     * @return Error list (if all okey return OK else error code)
     */
    ErrorList setLedPin(uint8_t newPinLed);


    /**
     * ----------------------------------------------------------------------------------------------------------------
     * --------------------------- Getters ----------------------------------------------------------------------------
     * ----------------------------------------------------------------------------------------------------------------
     */


    /**
     * 
     * @brief getter for pinRelay
     * 
     * @return number GPIO pin
     */
    uint8_t getRelayPin();


    /**
     * 
     * @brief getter for pinLed
     * 
     * @return number GPIO pin
     */
    uint8_t getLedPin();


    /**
     * 
     * @brief getter for name
     * 
     * @return String name relay
     */
    String getRelayName();



};




#endif
