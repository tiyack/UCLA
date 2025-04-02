////
////  main.cpp
////  Project 3
////
////  Created by Tiya Chokhani on 10/20/22.
////
//
//#include <iostream>
//#include <string>
//#include <cctype>
//#include <algorithm>
//using namespace std;
//
//
//bool isValidUppercaseStateCode(string stateCode)
//{
//    const string codes =
//        "AL.AK.AZ.AR.CA.CO.CT.DE.FL.GA.HI.ID.IL.IN.IA.KS.KY."
//        "LA.ME.MA.MD.MI.MN.MS.MO.MT.NE.NV.NH.NJ.NM.NY.NC.ND."
//        "OH.OK.OR.PA.RI.SC.SD.TN.TX.UT.VT.VA.WA.WV.WI.WY";
//    return (stateCode.size() == 2  &&
//            stateCode.find('.') == string::npos  &&  // no '.' in stateCode
//            codes.find(stateCode) != string::npos);  // match found
//}
//bool isValidLowercaseStateCode(string stateCode)
//{
//    const string codes =
//        "al.ak.az.ar.ca.co.ct.de.fl.ga.hi.id.il.in.ia.ka.ky."
//        "la.me.ma.md.mi.mn.ms.mo.mt.ne.nv.nh.nj.nm.ny.nc.nd."
//        "oh.ok.or.pa.ri.sc.sd.tn.tx.ut.vt.va.wa.wv.wi.wy";
//    return (stateCode.size() == 2  &&
//            stateCode.find('.') == string::npos  &&  // no '.' in stateCode
//            codes.find(stateCode) != string::npos);  // match found
//}
//bool isValidcaseStateCode(string stateCode)
//{
//    const string codes =
//        "Al.aL.Ak.aK.Az.aZ.Ar.aR.Ca.cA.Co.cO.Ct.cT.De.dE.Fl.fL.Ga.gA.Hi.hI."
//        "Id.iD.Il.iL.In.iN.Ia.iA.Ka.kA.Ky.kY.La.lA.Me.mE.Ma.mA.Md.mD.Mi.mI."
//        "Mn.mN.Ms.mS.Mo.mO.Mt.mT.Ne.nE.Nv.nV.Nh.nH.Nj.nJ.Nm.nM.Ny.nY.Nc.nC."
//        "Nd.nD.Oh.oH.Ok.oK.Or.oR.Pa.pA.Ri.rI.Sc.sC.Sd.sD.Tn.tN.Tx,tX.Ut.uT."
//        "Vt.vT.Va,vA.Wa.wA.Wv.wV.Wi.wI.Wy.wY"; //100
//    return (stateCode.size() == 2  &&
//            stateCode.find('.') == string::npos  &&  // no '.' in stateCode
//            codes.find(stateCode) != string::npos);  // match found
//}
//
//bool isValidPollString(string pollData){
//    string stateCode;
//    int k;
//
//    for(; pollData.size() > 0;){
//        if(pollData.size() < 2) //to return false if just one char is given
//            return false;
//        for(k = 0; k < 2; k++) //make first 2 chars of pollData into statecode
//            stateCode += pollData.at(k);
//        if(isValidUppercaseStateCode(stateCode) || isValidLowercaseStateCode(stateCode) || isValidcaseStateCode(stateCode)){ //check if valid state code
////            cerr << stateCode << " is a valid state code" << endl;
//            for(;k != pollData.size(); k ++){
//                if(pollData.at(k) == ','){
////                    cerr << "Need to start up again, state forecast has ended " << endl;
//                    break;
//                }
//                if(isdigit(pollData.at(k))){ // checking that next char is a digit
//                    k++; //to check next char
//                    if(isdigit(pollData.at(k))){ //to make sure only 2 digits are given
////                        cerr << pollData.at(k) << " next char is also dig!" << endl;
//                        k++;
//                    }
//                    if(isalpha(pollData.at(k))){ //checking to see next is char
////                        cerr << pollData.at(k) << " is an alphabet!" << endl;
//                    }
//                    else{ //if next char is not alpha
////                        cerr << "Need to return false, invalidcode here." << endl;
//                        return false;
//                    }
//                }
//                else{ //if next char isnt a digit
////                    cerr << "Need to return false, invalid code here2." << endl;
//                    return false;
//                }
//            } //break ends here
//            stateCode = "";
//            pollData.erase(pollData.begin(), pollData.begin()+k+1);
////            cerr << pollData << endl;
//        }
//        else{ //if not valid state here
////            cerr << "Need to return false. Invalid state code here 3." << endl;
//            return false;
//        }
//    }
//    return true;
//}
//
//int countSeats(string pollData, char party, int& seatCount){
//    if(!isValidPollString(pollData)){
////        cerr << "Not valid poll, returning 1\n";
//        return 1;
//    }
//    if(!isalpha(party)){
////        cerr << "Not a char, returning 2\n";
//        return 2;
//    }
//
//    string upperPollData; //converting the entire string to uppercase letters
//    for(int t = 0; t != pollData.size(); t++)
//        upperPollData += toupper(pollData.at(t));
//
//    char upperParty = toupper(party);
//    seatCount = 0; //making sure to start count with 0
//
//    //  cerr << upperPollData << endl << upperParty << endl;
//
//    for(; upperPollData.size() > 0;){
//        int i = 0;
//        for(i = 0; i != upperPollData.size(); i++){
//            if(upperPollData.at(i) == ','){
////                cerr << "New forecast, start again." << endl;
//                break;
//            }
//            if(upperPollData.at(i) == upperParty){
//                if(isdigit(upperPollData.at(i-2))){ //2 digit party votes
//                    string voteDig = "";
//                    voteDig = upperPollData.at(i-2); //adding first digit to new string
//                    voteDig += upperPollData.at(i-1); //adding next digit to new string
//                    seatCount += stoi(voteDig); //converting string to int and adding to seatcount
////                    cerr << "Count for " << upperParty << " is " << seatCount << endl;
//                }
//                else{ // one digit party votes
//                    string voteDig = "";
//                    voteDig = upperPollData.at(i-1);
//                    seatCount += stoi(voteDig);
////                    cerr << "Count for " << upperParty << " is " << seatCount << endl;
//                }
//            }
//            else
//                cerr << "This wasnt a party, " << upperPollData.at(i) << endl;
//        } //break ends here
//
//        upperPollData.erase(upperPollData.begin(), upperPollData.begin()+i+1);
////        cerr << upperPollData << endl;
//    }
//
//    cerr << "Seat count: " << seatCount << "\nEverything valid, returning 0" << endl;
//    return 0;
//}
//
//
//
//
//
//
//int main() {
////
////    string data;
////    cout << "Enter pollData: ";
////    getline(cin, data);
////
////    char chara;
////    cout << endl << "Enter party: ";
////    cin >> chara;
////
////    int seats = 0;
////    //cin >> seats;
////
////
////    cout << countSeats(data, chara, seats) << endl << seats << endl;
////
//    //testing 1 for isValidPollString
////    if (isValidPollString("CT5D,NY9R16D1I,VT,ne3r00D"))
////        cout << "Passed test 1: isValidPollString" << endl;
////    if (!isValidPollString("ZT5D,NY9R16D1I,VT,ne3r00D"))
////        cout << "Passed test 2: !isValidPollString" << endl;
////
//    //assert(isValidPollString("CT5D,NY9R16D1I,VT,ne3r00D"));
//    //assert(!isValidPollString("ZT5D,NY9R16D1I,VT,ne3r00D"));
//
//    //testing 2 for isValidPollString
////    if(isValidPollString(data))
////        cout << "true" << endl;
////    else
////        cout << "false" << endl;
////
////    data.erase(data.begin(), data.begin()+j);
////    cout << data;
//
//    if (isValidPollString("CT5D,NY9R16D1I,VT,ne3r00D"))
//        cout << "Passed test 1: isValidPollString(\"CT5D,NY9R16D1I,VT,ne3r00D\")" << endl;
//    if (!isValidPollString("ZT5D,NY9R16D1I,VT,ne3r00D"))
//        cout << "Passed test 2: !isValidPollString(\"ZT5D,NY9R16D1I,VT,ne3r00D\")" << endl;
//    int seats;
//    seats = -999;    // so we can detect whether countSeats sets seats
//    if (countSeats("CT5D,NY9R16D1I,VT,ne3r00D", 'd', seats) == 0  &&  seats == 21)
//        cout << "Passed test 3: countSeats(\"CT5D,NY9R16D1I,VT,ne3r00D\", 'd', seats)" << endl;
//
//    seats = -999;    // so we can detect whether countSeats sets seats
//    if (countSeats("CT5D,NY9R16D1I,VT,ne3r00D", '%', seats) == 2  &&  seats == -999)
//        cout << "Passed test 4: countSeats(\"CT5D,NY9R16D1I,VT,ne3r00D\", '%', seats)" << endl;
//    return 0;
//}
