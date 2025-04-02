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

void testone(int n)
{
    int s = 666;
    switch (n)
    {
                     default: {
        cout << "Bad argument" << endl;
            } break; case  1: {
        assert(!isValidPollString("3"));
            } break; case  2: {
        assert(!isValidPollString("#"));
            } break; case  3: {
        assert(!isValidPollString("3A"));
            } break; case  4: {
        assert(!isValidPollString("#A"));
            } break; case  5: {
        assert(!isValidPollString("C"));
            } break; case  6: {
        assert(!isValidPollString("C3"));
            } break; case  7: {
        assert(!isValidPollString("C#"));
            } break; case  8: { //FAILED
        assert(!isValidPollString("CA3"));
            } break; case  9: { //FAILED
        assert(!isValidPollString("CA73"));
            } break; case 10: {
        assert(!isValidPollString("CAD"));
            } break; case 11: {
        assert(!isValidPollString("CA$"));
            } break; case 12: {
        assert(!isValidPollString("CA7%"));
            } break; case 13: {
        assert(!isValidPollString("CA73%"));
            } break; case 14: {
        assert(!isValidPollString("CA738"));
            } break; case 15: {
        assert(!isValidPollString("CA738D"));
            } break; case 16: {
        assert(!isValidPollString("CA006D"));
            } break; case 17: {
        assert(!isValidPollString("XU44D"));
            } break; case 18: {
        assert(!isValidPollString("Xu44D"));
            } break; case 19: {
        assert(!isValidPollString("xU44D"));
            } break; case 20: {
        assert(!isValidPollString("xu44D"));
            } break; case 21: {
        assert(!isValidPollString("CA 55D"));
            } break; case 22: {
        assert(!isValidPollString("CA55 D"));
            } break; case 23: {
        assert(!isValidPollString("AZ4DE5R"));
            } break; case 24: {
        assert(!isValidPollString("AZ4D#5R"));
            } break; case 25: { //FAILED
        assert(!isValidPollString("AZ4D5"));
            } break; case 26: {
        assert(!isValidPollString("AZ4D5#5R"));
            } break; case 27: {
        assert(!isValidPollString("AZ4D5RI"));
            } break; case 28: {
        assert(!isValidPollString("FL15RI"));
            } break; case 29: {
        assert(!isValidPollString("FL15R@12D"));
            } break; case 30: { //FAILED
        assert(!isValidPollString("FL15R1"));
            } break; case 31: {
        assert(!isValidPollString("FL15R1@12D"));
            } break; case 32: {
        assert(!isValidPollString("FL15R12DE"));
            } break; case 33: {
        assert(!isValidPollString("FL15R 12D"));
            } break; case 34: {
        assert(!isValidPollString("UT4RHI2D"));
            } break; case 35: {
        assert(!isValidPollString(","));
            } break; case 36: {
        assert(!isValidPollString(",WY1R"));
            } break; case 37: { //FAILED
        assert(!isValidPollString("WY1R,"));
            } break; case 38: {
        assert(!isValidPollString("WY1R, MA8D,VT1D"));
            } break; case 39: {
        assert(!isValidPollString("WY1R,MA8D ,VT1D"));
            } break; case 40: {
        assert(!isValidPollString("WY1R,8D,VT1D"));
            } break; case 41: {
        assert(!isValidPollString("WY1R,MA8,VT1D"));
            } break; case 42: {
        assert(!isValidPollString("WY1R,GA10,VT1D"));
            } break; case 43: {
        assert(isValidPollString(""));
            } break; case 44: {
        assert(isValidPollString("CA"));
            } break; case 45: {
        assert(isValidPollString("Ca4D"));
            } break; case 46: {
        assert(isValidPollString("cA4D"));
            } break; case 47: {
        assert(isValidPollString("ca4D"));
            } break; case 48: {
        assert(isValidPollString("CA42D"));
            } break; case 49: {
        assert(isValidPollString("Ca42D"));
            } break; case 50: {
        assert(isValidPollString("cA42D"));
            } break; case 51: {
        assert(isValidPollString("ca42D"));
            } break; case 52: {
        assert(isValidPollString("CA9D"));
            } break; case 53: {
        assert(isValidPollString("CA4D"));
            } break; case 54: {
        assert(isValidPollString("CA0D"));
            } break; case 55: {
        assert(isValidPollString("CA89D"));
            } break; case 56: {
        assert(isValidPollString("CA09D"));
            } break; case 57: {
        assert(isValidPollString("CA00D"));
            } break; case 58: {
        assert(isValidPollString("CA4d"));
            } break; case 59: {
        assert(isValidPollString("CA42d"));
            } break; case 60: {
        assert(isValidPollString("CA4Z"));
            } break; case 61: {
        assert(isValidPollString("CA42Z"));
            } break; case 62: {
        assert(isValidPollString("KY5R1D"));
            } break; case 63: {
        assert(isValidPollString("FL15R12D"));
            } break; case 64: {
        assert(isValidPollString("GA10R4D"));
            } break; case 65: {
        assert(isValidPollString("GA4D10R"));
            } break; case 66: {
        assert(isValidPollString("CA11R22D3G1A7N"));
            } break; case 67: {
        assert(isValidPollString("LA2R1D3R"));
            } break; case 68: {
        assert(isValidPollString("WY1R,MA8D"));
            } break; case 69: {
        assert(isValidPollString("WY1R,MA8D,ID2R"));
            } break; case 70: {
        assert(isValidPollString("WY1R,MA,ID2R"));
            } break; case 71: {
        assert(isValidPollString("CA55D,KS10R,TX20R"));
            } break; case 72: {
        assert(isValidPollString("CA20D4R,KS4R,CA19D10R"));
            } break; case 73: {
        assert(isValidPollString("AL1D7R,AZ4D5R,AK4R,CA14R39D,CO3D4R"));
            } break; case 74: {
        assert(countSeats("3#QQ## QQ####", 'D', s) == 1);
            } break; case 75: {
        countSeats("3#QQ## QQ####", 'D', s);
        assert(s == 666);
            } break; case 76: {
        assert(countSeats("WV5R", '5', s) == 2);
            } break; case 77: {
        countSeats("WV5R", '5', s);
        assert(s == 666);
            } break; case 78: {
        assert(countSeats("TX38R", '5', s) == 2);
            } break; case 79: {
        countSeats("TX38R", '5', s);
        assert(s == 666);
            } break; case 80: {
        int r = countSeats("3#QQ## QQ####", '%', s);
        assert(r == 1  ||  r == 2);
            } break; case 81: {
        assert(countSeats("SD3R", 'R', s) == 0  &&  s == 3);
            } break; case 82: {
        assert(countSeats("SD3r", 'R', s) == 0  &&  s == 3);
            } break; case 83: {
        assert(countSeats("SD3R", 'r', s) == 0  &&  s == 3);
            } break; case 84: {
        assert(countSeats("SD3r", 'r', s) == 0  &&  s == 3);
            } break; case 85: {
        assert(countSeats("NY29D", 'D', s) == 0  &&  s == 29);
            } break; case 86: {
        assert(countSeats("NY29d", 'D', s) == 0  &&  s == 29);
            } break; case 87: {
        assert(countSeats("NY29D", 'd', s) == 0  &&  s == 29);
            } break; case 88: {
        assert(countSeats("NY29d", 'd', s) == 0  &&  s == 29);
            } break; case 89: {
        assert(countSeats("UT6L", 'D', s) == 0  &&  s == 0);
            } break; case 90: {
        assert(countSeats("WA11G", 'D', s) == 0  &&  s == 0);
            } break; case 91: {
        assert(countSeats("WA3G1D5L2R", 'L', s) == 0  &&  s == 5);
            } break; case 92: {
        assert(countSeats("WA03G01D05L12R", 'L', s) == 0  &&  s == 5);
            } break; case 93: {
        assert(countSeats("WA03G01D05L12R", 'R', s) == 0  &&  s == 12);
            } break; case 94: {
        assert(countSeats("LA2R6D3R", 'R', s) == 0  &&  s == 5);
            } break; case 95: {
        assert(countSeats("KS,WY,VT,HI", 'G', s) == 0  &&  s == 0);
            } break; case 96: {
        assert(countSeats("KS4R,WY3G,VT1I,HI2D", 'G', s) == 0  &&  s == 3);
            } break; case 97: {
        assert(countSeats("KS14R,WY13G,VT11I,HI12D", 'G', s) == 0  &&  s == 13);
            } break; case 98: {
        assert(countSeats("KS4R,WY3G,VT1I,HI2D", 'L', s) == 0  &&  s == 0);
            } break; case 99: { //FAILED
        assert(countSeats("IL11R,DE5G,MD7D", 'D', s) == 0  &&  s == 7);
            } break; case 100: {
        assert(countSeats("KS4R,WY1R,MA9D,ID2R,HI2D", 'R', s) == 0  &&  s == 7);
            } break; case 101: {
        assert(countSeats("AL1D6R,CT5D,KY5R1D,MI9R4D,NJ7D5R", 'R', s) == 0  &&  s == 25);
            } break; case 102: {
        assert(countSeats("CA39D14R,FL15R11D,TX11D25R", 'R', s) == 0  &&  s == 54);
            } break; case 103: {
        assert(countSeats("MI4D4R5R,TN1D4R1D3R", 'R', s) == 0  &&  s == 16);
            } break; case 104: {
        assert(countSeats( //FAILED
        "AL1D6R,AK1R,AZ4D5R,AR4R,CA39D14R,CO3D4R,CT5D,DE1D,FL11D16R,"
        "GA4D10R,HI2D,ID2R,IL11D7R,IN2D7R,IA1D3R,KS4R,KY1D5R,LA1D5R,"
        "ME1D1R,MD7D1R,MA9D,MI5D9R,MN5D3R,MS1D3R,MO2D6R,MT1R,NE3R,"
        "NV3D1R,NH2D,NJ7D5R,NM2D1R,NY18D9R,NC3D10R,ND1R,OH4D12R,"
        "OK5R,OR4D1R,PA1D11R,RI2D,SC1D6R,SD1R,TN2D7R,TX11D25R,UT4R,"
        "VT1D,VA4D7R,WA6D4R,WV3R,WI3D5R,WY1R", 'D', s) == 0  &&  s == 190);
            } break; case 105: {
        assert(countSeats( //FAILED
        "AL1D6R,AK1R,AZ4D5R,AR4R,CA39D14R,CO3D4R,CT5D,DE1D,FL11D16R,"
        "GA4D10R,HI2D,ID2R,IL11D7R,IN2D7R,IA1D3R,KS4R,KY1D5R,LA1D5R,"
        "ME1D1R,MD7D1R,MA9D,MI5D9R,MN5D3R,MS1D3R,MO2D6R,MT1R,NE3R,"
        "NV3D1R,NH2D,NJ7D5R,NM2D1R,NY18D9R,NC3D10R,ND1R,OH4D12R,"
        "OK5R,OR4D1R,PA1D11R,RI2D,SC1D6R,SD1R,TN2D7R,TX11D25R,UT4R,"
        "VT1D,VA4D7R,WA6D4R,WV3R,WI3D5R,WY1R", 'R', s) == 0  &&  s == 239);
            } break; case 106: {
        assert(countSeats( //FAILED
        "AL1D6R,AK1R,AZ4D5R,AR4R,CA39D14R,CO3D4R,CT5D,DE1D,FL11D16R,"
        "GA4D10R,HI2D,ID2R,IL11D7R,IN2D7R,IA1D3R,KS4R,KY1D5R,LA1D5R,"
        "ME1D1R,MD7D1R,MA9D,MI5D9R,MN5D3R,MS1D3R,MO2D6R,MT1R,NE3R,"
        "NV3D1R,NH2D,NJ7D5R,NM2D1R,NY18D9R,NC3D10R,ND1R,OH4D12R,"
        "OK5R,OR4D1R,PA1D11R,RI2D,SC1D6R,SD1R,TN2D7R,TX11D25R,UT4R,"
        "VT1D,VA4D7R,WA6D4R,WV3R,WI3D5R,WY1R", 'I', s) == 0  &&  s == 0);
            }
    }
}



int main() {

    cout << "Enter test number: ";
        int n;
        cin >> n;
        testone(n);
        cout << "Passed if there was no undefined behavior." << endl;
    
//    assert(isValidPollString("CT5D,NY9R16D1I,VT,ne3r00D"));
//    assert(!isValidPollString("ZT5D,NY9R16D1I,VT,ne3r00D")); //invalid state code
//    assert(isValidPollString("cA0t")); //just one state code with 0 as the result
//    assert(isValidPollString("")); //empty string
//    assert(!isValidPollString("c")); //only one character
//    assert(!isValidPollString("wD,")); //only invalid state code
//    assert(!isValidPollString("00000car4")); //starts with digits
//    assert(!isValidPollString("Ny&&**()#)#)_")); //valid code but invalid forecast
//    assert(!isValidPollString(",")); //just a comma
//    assert(isValidPollString("mO9r9r5r60t3r,nY7v")); //multiple same party results
//    assert(!isValidPollString("Mo456j")); //3 digit long result
//    assert(!isValidPollString(",Ca")); //starts with a comma
//    assert(!isValidPollString("Ca,,nY99y,nj07f5r4e8c")); //double comma
//    assert(!isValidPollString(" ")); //just a space
//    assert(!isValidPollString("mO9r9r 5r60t3r,nY7v")); //space between poll results
//    assert(!isValidPollString("Ny77f9h7g5f4w2q1k,vt9hg")); // 2 char long party name
//    assert(isValidPollString("mO9r9r5r60t3r,nY7v,")); //comma at the end
//    assert(!isValidPollString("&")); //invalid state code
//    cerr << "All tests for isValidPollString succeeded" << endl;
////invalid char
////    string data;
////    cout << "Enter pollData: ";
////    getline(cin, data);
////    char r;
////    cin >> r;
////    int seat;
////    cin >> seat;
////
////    int k = countSeats(data, r, seat);
////    cout << "Returned: " << r <<" Seats are: " << seat;
//
//    int seats;
//    seats = -999; // so we can detect whether countSeats sets seats
//    assert(countSeats("CT5D,NY9R16D1I,VT,ne3r00D", 'd', seats) == 0  &&  seats == 21);
//    seats = -999; // to detect if countSeats changes seats and if it returns 2 for invalid party
//    assert(countSeats("CT5D,NY9R16D1I,VT,ne3r00D", '%', seats) == 2  &&  seats == -999);
//    seats = 3993; //to check that returns 1 for invalid pollData
//    assert(countSeats("cA5r33e,nY00d432f", 'r', seats) == 1 && seats == 3993);
//    //to check for multiple party results for the same state
//    assert(countSeats("CA44r3d0g9r5n8f88h5r1r", 'r', seats) == 0 && seats == 59);
//    //to check for multiple party results and multiple states
//    assert(countSeats("nJ,ar20m,AZ6n6m4m,oh", 'm', seats) == 0 && seats == 30);
//    seats = 60; //to check for empty string
//    assert(countSeats("", 'm', seats) == 0 && seats == 0);
//    //to check when pollData doesnt include party
//    assert(countSeats("NY9R16D1I", 'm', seats) == 0 && seats == 0);
//    //to check for lower case party and upper case party result and for party result being doble digit starting with 0
//    assert(countSeats("AZ44R3D3d3D,nY01R5n01d6T", 'd', seats) == 0 && seats == 10); //
//    cerr << "All tests for CountSeats succeeded" << endl;
//    assert(countSeats("AZ44a3D3d3D,nY01a5n01d6T", 'a', seats) == 0 && seats == 45); //
//    cerr << "All tests for CountSeats succeeded" << endl; //error fuck
//


    
    return 0;
}
