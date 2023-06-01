
# Embedded Project for StackFusion

Using ESP32 to connect to internet and to GET API posted at the link https://fastag-internal.parkzap.com/account/mockable_test/

Not a complete solution but I've documented my approach below.


## **Approach**
### *Prerequisite*
1. WiFi library to connect to the internet.
2. HTTP Client library for GET Method
3. SD Card Library to connect to SD Card Module(SPI) 
4. JSON Parser to parse the data from API

### *Plan to execute*
    Fetch data from the API and save it in a string. 
    Parse that string into a JSON object using the Arduino_JSON library.
    Iterate over the JSON. Create a file with filename "Key" and store "Value" in it
    
```c

writeFile(SD,"JSONArray[i][0]","JSONArray[i][1]")
//Usage writeFile(SD,"/hello.txt","Hello World!")

```
    All this is done in the setup function.

    In the loop function
    Serial.read() the required key and use that string as parameter for readFile()
```c

readFile(SD,Serial.read())


```
    if it exists, it'll return value it contains, otherwise will throw an error.
This approach is better than searching as that has an O(N) Time Complexity. 
My approach has a time complexitiy of O(1)

## **Problems Faced**
    Standard SD card library uses 8.3 filename system which states that,
    the maximum filename length should be of 8 letters and extension maximum of 3.
    Fur Elise.mp3 becomes FURELI~1.MP3
    You may have noticed this in the DOS era.
    This can be circumvented by using a better SD Card library.
    greiman / SdFat library should fix this as it can even support exFAT formatted SD cards.
    The 18 characted filename shouldn't pose a problem now. 
