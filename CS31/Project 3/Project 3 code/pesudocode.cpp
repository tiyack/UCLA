//
//  pesudocode.cpp
//  Project 3
//
//  Created by Tiya Chokhani on 10/23/22.
//

#include <stdio.h>

//
//isValidUppercaseStateCode
//    list of valid uppercase state codes seperated by a '.'
//    check if the stateCode is 2 char and that it does not include a '.' and that the 2 characters can be found in the string of codes
//    returns true if yes and false if no
//
//isValidLowercaseStateCode
//    list of valid lowercase state codes seperated by a '.'
//    check if the stateCode is 2 char and that it does not include a '.' and that the 2 characters can be found in the string of codes
//    returns true if yes and false if no
//
//isValidOtherStateCode
//    list of valid case state codes with different cases seperated by a '.'
//    check if the stateCode is 2 char and that it does not include a '.' and that the 2 characters can be found in the string of codes
//    returns true if yes and false if no
//
//isValidPollString
//    for the number of characters in pollData grater than 0
//        if the string has less than 2 characters
//            return false
//        for every second character in the string
//            if its a valid stateCode
//                for every character in the string
//                    if the character is a ','
//                        break
//                    if the next character is a digit
//                        if the next chacter is a digit
//                        if the next character is a aplhabet
//                        else return false
//                    else return false
//                set stateCode to an empty string
//                if pollData has more chacters left to check
//                    remove all the characters already checked from pollData and one more
//                else remove only all the characters already checked from pollData
//            else return false because its an invalid state code
//    return true if everything pases
//
//countSeats
//    if a valid pollString hasnt been given
//        return 1
//    if the party isnt an aplhabet
//        return 2
//
//    for all the characters in pollData
//        make them all uppercase and store it in upperPollData
//    make party uppercase and store it in uppperParty
//    set seatCount to 0
//
//    for the number of characters in upperPollData grater than 0
//        for all the characters in upperPollData
//            if the character is ','
//                break
//            if character is the same as the party
//                if the character 2 characters before the party is a digit
//                    make the 2 digits before party into a char
//                    convert this char to an integer and add it to seatCount
//                else
//                    make the character before the party a different char
//                    convert this char to an integer and add it to seatCount
//
//        if the number of characters in upperPollData is more than those already checked
//            reomve all the characters checked and one more
//        else remove only all the characters already checked
//    return 0
//
//

        
