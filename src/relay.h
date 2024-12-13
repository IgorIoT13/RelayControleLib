#ifndef RELAY
#define RELAY
#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/semphr.h>

#include "ErrorList.h"

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
        bool enableWorkState;

        void (*func_ON)(void);
        void (*func_OFF)(void);

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
         * 
         * @brief Manual off relay
         * 
         * @return Error if something was wrong
         */
        ErrorList offRelay();


        /**
         * 
         * @brief Manual on relay
         * 
         * @return Error if something was wrong
         */        
        ErrorList onRelay();


        /**
         * @brief Disable work relay(Off)
         * @note This function turn off tick for relay
         * 
         * 
         * @return Error if something was wrong
         */
        ErrorList disableWork();


        /**
         * @brief Enable work relay(On)
         * @note This function turn on tick for relay
         * 
         * 
         * @return Error if something was wrong
         */
        ErrorList enableWork();



        /**
         * ----------------------------------------------------------------------------------------------------------------
         * --------------------------- Automatic controle -----------------------------------------------------------------
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
        ErrorList offState();


        /**
         * 
         * @brief Set state of relay true or on relay
         * 
         * @return Error list. if all okey return OK else error code
         * 
         */
        ErrorList onState();


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
     * @brief set function on on relay
     */
    void setOnFunc(void (*onFunc)(void));

    /**
     * @brief set function on off relay
     */
    void setOffFunc(void (*offFunc)(void));


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




    private:
/**
 * ____________________________________________________________________________________________________________________
 * _______________________________ Service logic ______________________________________________________________________
 * ____________________________________________________________________________________________________________________
 */


        /**
         * ----------------------------------------------------------------------------------------------------------------
         * --------------------------- Objectc values checkers ----------------------------------------------------------------------------
         * ----------------------------------------------------------------------------------------------------------------
         */


        /**
         * @brief Check errors in values
         * 
         * @return ERR_VALUER_EMPTY - name uncorect or ERR_VALUER_UNCORECT if GPIO pin are incorects
         */
        ErrorList checkValues();


        /**
         * @brief Check pin relay corect or uncorect his
         * @note Check values of pin inside object. If valuer is uncorect return error 
         * 
         * @return ERR_VALUER_UNCORECT if GPIO pin are incorect or ALL_OK if all good
         */
        ErrorList checkObjectPinRelay();


        /**
         * @brief Check pin led corect or uncorect his
         * @note Check values of pin inside object. If valuer is uncorect return error 
         * 
         * @return ERR_VALUER_UNCORECT if GPIO pin are incorect or ALL_OK if all good
         */
        ErrorList checkObjectPinLed();

        /**
         * @brief Check name
         * @note Check values of name inside object. If name is uncorect (empty) return error 
         * 
         * @return ERR_VALUER_EMPTY - name uncorect
         */
        ErrorList checkObjectName();


        /**
         * ----------------------------------------------------------------------------------------------------------------
         * --------------------------- External values checkers ----------------------------------------------------------------------------
         * ----------------------------------------------------------------------------------------------------------------
         */


        /**
         * @brief Check external pin
         * @note if something is not good return err
         * 
         * @param pin external pin for check
         * 
         * @return ERR_VALUER_UNCORECT if GPIO pin are incorects else ALL_OK
         */
        ErrorList checkPin(uint8_t pin);


        /**
         * @brief Check input name
         * @note if something is not good return err
         * 
         * @param name name for check
         * 
         * @return ERR_VALUER_EMPTY - name uncorect
         */
        ErrorList checkName(String name);

        /**
         * @brief Check all param 
         * @note Check all params to insert in object or to use
         * 
         * @param name - name relay
         * @param pinRelay - GPIO pin number (relay)
         * @param pinRelay - GPIO pin number (led)
         * 
         * @return ERR_VALUER_EMPTY - name uncorect or ERR_VALUER_UNCORECT if GPIO pin are incorects
         */
        ErrorList checkAllValues(String name, uint8_t pinRelay, uint8_t pinLed);



};




#endif
