#include <iostream>
#include <istream>
#include <fstream>
#include <string>

using namespace std;

//declare functions
double hit_percent(int BS,string specialProp[5]);
double wound_percent(int e_toughness,int strength,string specialProp[5]);
double save_percent(int e_sv, int e_inv_sv,int AP,string specialProp[5]);

int main()
{
    ifstream unit;//document holding the units stats
    int counter=0;
    int unitStats[12];//array storing all of the units stats

    string unitName = "None";//variable storing units name

    unit.open("./Units/HQ/DaemonPrinceofNurgle.txt");
    if(!unit)
    {
        cout<<"Error File Not Found"<<endl;
        return -1;
    }

    string storage="None";//storage variable to determine when the melee weapon list starts
    bool melee=false;//determines where the melee weapon list begins
    string unitWeapons[12]={""};//declares the array to store the ranged weapons
    string unitMelee[12]={""};//declares the array to store the melee weapons
    string permanentWeapons[5]={""};//declares an array to store any ranged weapons that cannot be switched out
    string permanentMelee[5]={""};//declares an array to store any melee weapons that cannot be switched out
    int x=-1;
    bool permanent=false;//variable to check if there are any weapons that cannot be switched out
    while(true)
    {
        if(unit.eof())
            break;
        if(counter==0)
        {
            getline(unit,unitName);//gets the name of the unit
        }
        else if(counter>0 && counter <13)
        {
            unit>>unitStats[counter-1];//gets the stats of the unit
        }
        else if(counter>=13)
        {
            getline(unit,storage);
            if(melee)
            {
                if(storage=="PERMANENT")
                {
                    permanent=true;
                }
                else if(!permanent)
                    unitMelee[x]=storage;
                else
                    permanentMelee[x]=storage;
            }
            if(storage=="Melee")
            {
                melee=true;
                permanent=false;
                x=-1;
            }
            else if(melee==false && storage!="Weapons")
            {
                if(storage=="PERMANENT")
                {
                    permanent=true;
                }
                else if(!permanent)
                    unitWeapons[x]=storage;
                else
                    permanentWeapons[x]=storage;
            }
            x++;
        }
        counter++;
    }
    unit.close();
    if(unitWeapons[11]=="" && unitWeapons[12]!="")
        unitWeapons[12]="";
    //Puts the unitStats array into variables for easier use
    int models=unitStats[0];
    bool champion=unitStats[1];
    int pointCost=unitStats[2];
    int BS=unitStats[3];
    int WS=unitStats[4];
    int strength=unitStats[5];
    int toughness=unitStats[6];
    int wounds=unitStats[7];
    int attacks=unitStats[8];
    int sv=unitStats[9];
    int inv_sv=unitStats[10];
    int ld=unitStats[11];


    int e_sv=3;
    int e_inv=5;
    int e_toughness=4;

    ofstream results;
    results.open("Results.txt");
    if(!results)
    {
        cout<<"Error Finding Results File"<<endl;
        return -2;
    }
    results<<unitName<<endl;
    ifstream weapon;//document holding theel weapon stats
    //declares variables to store weapon data
    string weaponName;
    int weaponStats[4]={0};


    for(int a=0;unitWeapons[a]!="";a++)//calculates the damage potential of the ranged weapons
    {
        string weaponFile="./Weapons/"+unitWeapons[a]+".txt";
        weapon.open(weaponFile);
        string weaponSpecial[5]={""};
        if(!weapon)
        {
            cout<<"Error Finding Weapon File"<<endl;
            return -1;
        }
        counter=0;
        while(true)
        {
            if(weapon.eof())
                break;
            if(counter==0)
                getline(weapon,weaponName);
            else if(counter>0 && counter <5)
            {
                weapon>>weaponStats[counter-1];//gets the stats of the unit
            }
            else if(counter>=5)
            {
                weapon>>weaponSpecial[counter-5];
            }
            counter++;
        }
        weapon.close();
        //puts weapon values into useable variables
        int weaponPointCost=weaponStats[0];
        double shots=weaponStats[1];
        int w_strength=weaponStats[2];
        int AP=weaponStats[3];
        int damage=weaponStats[4];
        //finds the percentage for damage
        double hitPercent=hit_percent(BS,weaponSpecial);
        cout<<hitPercent<<endl;
        double woundPercent=wound_percent(e_toughness,w_strength,weaponSpecial);
        cout<<woundPercent<<endl;
        double savePercent=save_percent(e_sv,e_inv,AP,weaponSpecial);
        cout<<savePercent<<endl;
        double damageDealt=shots*hitPercent*woundPercent*savePercent*damage;
        cout<<damageDealt<<endl;
    }

    for(int a=0;unitMelee[a]!="";a++)//calculates the damage potential of the melee weapons
    {
        string weaponFile="./Melee/"+unitMelee[a]+".txt";
        weapon.open(weaponFile);
        string weaponSpecial[5]={""};
        if(!weapon)
        {
            cout<<"Error Finding Melee Weapon File"<<endl;
            return -1.5;
        }
        counter=0;
        while(true)
        {
            if(weapon.eof())
                break;
            if(counter==0)
                getline(weapon,weaponName);
            else if(counter>0 && counter <5)
            {
                weapon>>weaponStats[counter-1];//gets the stats of the unit
            }
            else if(counter>=5)
            {
                weapon>>weaponSpecial[counter-5];
            }
            counter++;
        }
        weapon.close();
        //puts weapon values into useable variables
        int weaponPointCost=weaponStats[0];
        int w_strength=weaponStats[1];
        int AP=weaponStats[2];
        int damage=weaponStats[3];
        //finds the percentage for damage
        double hitPercent=hit_percent(WS,weaponSpecial);
        double woundPercent=wound_percent(e_toughness,strength,weaponSpecial);
        double savePercent=save_percent(e_sv,e_inv,AP,weaponSpecial);
        //applies special properties which ONLY affect the final damage calculation (ie attacks, or damage modifier)
        int attackBonus=0;
        for(int n=0;weaponSpecial[n]!="";n++)
        {
            if(weaponSpecial[n]=="OneExtraAttack")
                attackBonus=1;
            else if(weaponSpecial[n]=="ThreeExtraAttacks")
                attackBonus=3;
        }
        double damageDealt=(attacks+attackBonus)*hitPercent*woundPercent*savePercent*damage;
        results<<weaponName<<endl;
        results<<"Average Damage Dealt: "<<damageDealt<<endl;
        results<<"Damgage Per Point: "<<damageDealt/(pointCost+weaponPointCost)<<endl<<endl;
    }
    return 0;
}

double hit_percent(int BS,string specialProp[5])
{
    for(int n=0;specialProp[n]!="";n++)
    {
        if(specialProp[n]=="MinusOneToHit")
            BS+=1;
    }
    double hit=0.0;
    switch(BS)
    {
        case 1:
        {
            hit = 5.0/6.0;
            break;
        }
        case 2:
        {
            hit = 5.0/6.0;
            break;
        }
        case 3:
        {
            hit = 4.0/6.0;
            break;
        }
        case 4:
        {
            hit = 3.0/6.0;
            break;
        }
        case 5:
        {
            hit = 2.0/6.0;
            break;
        }
        case 6:
        {
            hit = 1.0/6.0;
            break;
        }
    }
    return hit;
}
double wound_percent(int e_toughness, int strength,string specialProp[5])
{
    double percent=0;
    if(strength >= e_toughness*2)
        percent=5.0/6.0;
    else if(strength > e_toughness)
        percent=4.0/6.0;
    else if(strength == e_toughness)
        percent=3.0/6.0;
    else if(strength <= e_toughness/2)
        percent=1.0/6.0;
    else if(strength < e_toughness)
        percent=2.0/6.0;
    return percent;
}

double save_percent(int e_sv, int e_inv_sv, int AP,string specialProp[5])
{
    double save=0.0;
    if(e_sv+AP > 7 && e_inv_sv==0)
        return 1;
    if((e_sv+AP<e_inv_sv && e_inv_sv != 0) or e_inv_sv==0)
    {
        switch(e_sv + AP)
        {
            case 1:
            {
                save = 1.0/6.0;
                break;
            }
            case 2:
            {
                save = 1.0/6.0;
                break;
            }
            case 3:
            {
                save = 2.0/6.0;
                break;
            }
            case 4:
            {
                save = 3.0/6.0;
                break;
            }
            case 5:
            {
                save = 4.0/6.0;
                break;
            }
            case 6:
            {
                save = 5.0/6.0;
                break;
            }
        }
    }
    else
    {
        switch(e_inv_sv)
        {
            case 1:
            {
                save = 5.0/6.0;
                break;
            }
            case 2:
            {
                save = 5.0/6.0;
                break;
            }
            case 3:
            {
                save = 4.0/6.0;
                break;
            }
            case 4:
            {
                save = 3.0/6.0;
                break;
            }
            case 5:
            {
                save = 2.0/6.0;
                break;
            }
            case 6:
            {
                save = 1.0/6.0;
                break;
            }
        }
    }
    return save;
}
