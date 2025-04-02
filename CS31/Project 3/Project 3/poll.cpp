//
//  main.cpp
//  Project 3
//
//  Created by Tiya Chokhani on 10/20/22.
//

//everything is working right now but needs thorough testing.
#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>
#include <cassert>
using namespace std;


bool isValidUppercaseStateCode(string stateCode)
{
    const string codes =
        "AL.AK.AZ.AR.CA.CO.CT.DE.FL.GA.HI.ID.IL.IN.IA.KS.KY."
        "LA.ME.MA.MD.MI.MN.MS.MO.MT.NE.NV.NH.NJ.NM.NY.NC.ND."
        "OH.OK.OR.PA.RI.SC.SD.TN.TX.UT.VT.VA.WA.WV.WI.WY";
    return (stateCode.size() == 2  &&
            stateCode.find('.') == string::npos  &&  // no '.' in stateCode
            codes.find(stateCode) != string::npos);  // match found
}
bool isValidLowercaseStateCode(string stateCode)
{
    const string codes =
        "al.ak.az.ar.ca.co.ct.de.fl.ga.hi.id.il.in.ia.ka.ky."
        "la.me.ma.md.mi.mn.ms.mo.mt.ne.nv.nh.nj.nm.ny.nc.nd."
        "oh.ok.or.pa.ri.sc.sd.tn.tx.ut.vt.va.wa.wv.wi.wy";
    return (stateCode.size() == 2  &&
            stateCode.find('.') == string::npos  &&  // no '.' in stateCode
            codes.find(stateCode) != string::npos);  // match found
}
bool isValidOtherStateCode(string stateCode)
{
    const string codes =
        "Al.aL.Ak.aK.Az.aZ.Ar.aR.Ca.cA.Co.cO.Ct.cT.De.dE.Fl.fL.Ga.gA.Hi.hI."
        "Id.iD.Il.iL.In.iN.Ia.iA.Ka.kA.Ky.kY.La.lA.Me.mE.Ma.mA.Md.mD.Mi.mI."
        "Mn.mN.Ms.mS.Mo.mO.Mt.mT.Ne.nE.Nv.nV.Nh.nH.Nj.nJ.Nm.nM.Ny.nY.Nc.nC."
        "Nd.nD.Oh.oH.Ok.oK.Or.oR.Pa.pA.Ri.rI.Sc.sC.Sd.sD.Tn.tN.Tx,tX.Ut.uT."
        "Vt.vT.Va,vA.Wa.wA.Wv.wV.Wi.wI.Wy.wY"; //100
    return (stateCode.size() == 2  &&
            stateCode.find('.') == string::npos  &&  // no '.' in stateCode
            codes.find(stateCode) != string::npos);  // match found
}

bool isValidPollString(string pollData){
    string stateCode;
    int k;
    
    for(; pollData.size() > 0;){ //to loop till pollData string is empty
        if(pollData.size() < 2) //to return false if just one char is given
            return false;
        for(k = 0; k < 2; k++) //make first 2 chars of pollData into statecode
            stateCode += pollData.at(k);
        if(isValidUppercaseStateCode(stateCode) || isValidLowercaseStateCode(stateCode) || isValidOtherStateCode(stateCode)){ //check if valid state code
//            cerr << stateCode << " is a valid state code" << endl;
            for(;k != pollData.size(); k ++){
                if(pollData.at(k) == ','){//state forecast has ended so it needs to being again
//                    cerr << "Need to start up again, state forecast has ended " << endl;
                    break;
                }
                if(isdigit(pollData.at(k))){ // checking that next char is a digit
//                    cerr << pollData.at(k) << " is a digit." << endl;
                    k++; //to check next char
                    if(isdigit(pollData.at(k))){ //to make sure only 2 digits are given
//                        cerr << pollData.at(k) << " next char is also dig!" << endl;
                        k++;
                    }
                    if(isalpha(pollData.at(k))){ //checking to see next is party
//                        cerr << pollData.at(k) << " is an alphabet!" << endl;
                    }
                    else{ //if next char is not a party
//                        cerr << "Need to return false, invalidcode here." << endl;
                        return false;
                    }
                }
                else{ //if next char isnt a digit
//                    cerr << "Need to return false, invalid code here2." << endl;
                    return false;
                }
            } //break ends here
            
            stateCode = "";
            if(pollData.size() > k){
                pollData.erase(pollData.begin(), pollData.begin()+k+1);
//                cerr << pollData << endl;
            }
            else{
                pollData.erase(pollData.begin(), pollData.begin()+k);
//                cerr << pollData << endl;
            }
        }
        else{ //if not valid state here
//            cerr << "Need to return false. Invalid state code here 3." << endl;
            return false;
        }
    }
    return true;
}

int countSeats(string pollData, char party, int& seatCount){
    if(!isValidPollString(pollData)){
//        cerr << "Not valid poll, returning 1\n";
        return 1;
    }
    if(!isalpha(party)){
//        cerr << "Not a char, returning 2\n";
        return 2;
    }
    
    string upperPollData; //converting the entire string to uppercase letters
    for(int t = 0; t != pollData.size(); t++)
        upperPollData += toupper(pollData.at(t));
    
    char upperParty = toupper(party);
    seatCount = 0; //making sure to start count with 0
  
//      cerr << upperPollData << endl << upperParty << endl;
    
    for(; upperPollData.size() > 0;){
        int i = 0;
        for(i = 0; i != upperPollData.size(); i++){
            if(upperPollData.at(i) == ','){
//                cerr << "New forecast, start again." << endl;
                break;
            }
            if(upperPollData.at(i) == upperParty){
                //cerr << "hello" << endl;
                //cerr << upperPollData[i-2]<< endl;
                //cerr << upperPollData[i-1]<< endl;
                //cerr << upperPollData[i]<< endl;
                if(isdigit(upperPollData.at(i-2))){ //2 digit party votes
                    char ch = '0';
                    ch = upperPollData.at(i-1) - ch;
                    int num = ch;
                    //cerr << num << endl;
                    seatCount += num;
//                    cerr << "Seat Count is: " << seatCount << endl;

                    ch = '0';
                    ch = upperPollData.at(i-2) - ch;
                    num = ch;
                    //cerr << num << endl;
                    seatCount = seatCount + (10 * num);
//                    cerr << "Seat Count is: " << seatCount << endl;

                }
                else{ // one digit party votes

                    char ch = '0';
                    ch = upperPollData.at(i-1) - ch;
                    //cerr << ch << endl;
                    //cerr << "here" << endl;
                    //cerr << upperPollData[i-1];
                    int num = ch ;
                   // cerr << num << endl;
                    seatCount += num;
//                    cerr << "Seat Count is: " << seatCount << endl;
                }
            }
//            else
//                cerr << "This wasnt a party, " << upperPollData.at(i) << endl;
        } //break ends here
        
        if(upperPollData.size() > i)
            upperPollData.erase(upperPollData.begin(), upperPollData.begin()+i+1);
        else
            upperPollData.erase(upperPollData.begin(), upperPollData.begin()+i);
//        cerr << upperPollData << endl;
    }
    
//    cerr << "Seat count: " << seatCount << "\nEverything valid, returning 0" << endl;
    return 0;
}





int main() {

    assert(isValidPollString("CT5D,NY9R16D1I,VT,ne3r00D"));
    assert(!isValidPollString("ZT5D,NY9R16D1I,VT,ne3r00D")); //invalid state code
    assert(isValidPollString("cA0t")); //just one state code with 0 as the result
    assert(isValidPollString("")); //empty string
    assert(!isValidPollString("c")); //only one character
    assert(!isValidPollString("wD,")); //only invalid state code
    assert(!isValidPollString("00000car4")); //starts with digits
    assert(!isValidPollString("Ny&&**()#)#)_")); //valid code but invalid forecast
    assert(!isValidPollString(",")); //just a comma
    assert(isValidPollString("mO9r9r5r60t3r,nY7v")); //multiple same party results
    assert(!isValidPollString("Mo456j")); //3 digit long result
    assert(!isValidPollString(",Ca")); //starts with a comma
    assert(!isValidPollString("Ca,,nY99y,nj07f5r4e8c")); //double comma
    assert(!isValidPollString(" ")); //just a space
    assert(!isValidPollString("mO9r9r 5r60t3r,nY7v")); //space between poll results
    assert(!isValidPollString("Ny77f9h7g5f4w2q1k,vt9hg")); // 2 char long partty name
    cerr << "All tests for isValidPollString succeeded" << endl;

//    string data;
//    cout << "Enter pollData: ";
//    getline(cin, data);
//    char r;
//    cin >> r;
//    int seat;
//    cin >> seat;
//
//    int k = countSeats(data, r, seat);
//    cout << "Returned: " << r <<" Seats are: " << seat;
    
    int seats;
    seats = -999; // so we can detect whether countSeats sets seats
    assert(countSeats("CT5D,NY9R16D1I,VT,ne3r00D", 'd', seats) == 0  &&  seats == 21);
    seats = -999; // to detect if countSeats changes seats and if it returns 2 for invalid party
    assert(countSeats("CT5D,NY9R16D1I,VT,ne3r00D", '%', seats) == 2  &&  seats == -999);
    seats = 3993; //to check that returns 1 for invalid pollData
    assert(countSeats("cA5r33e,nY00d432f", 'r', seats) == 1 && seats == 3993);
    //to check for multiple party results for the same state
    assert(countSeats("CA44r3d0g9r5n8f88h5r1r", 'r', seats) == 0 && seats == 59);
    //to check for multiple party results and multiple states
    assert(countSeats("nJ,ar20m,AZ6n6m4m,oh", 'm', seats) == 0 && seats == 30);
    seats = 60; //to check for empty string
    assert(countSeats("", 'm', seats) == 0 && seats == 0);
    //to check when pollData doesnt include party
    assert(countSeats("NY9R16D1I", 'm', seats) == 0 && seats == 0);
    //to check for lower case party and upper case party result and for party result being doble digit starting with 0
    assert(countSeats("AZ44R3D3d3D,nY01R5n01d6T", 'd', seats) == 0 && seats == 10);
    
    cerr << "All tests for CountSeats succeeded" << endl;



    
    return 0;
}
