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
    int unitStats[11];//array storing all of the units stats

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
        else if(counter>0 && counter <12)
        {
            unit>>unitStats[counter-1];//gets the stats of the unit
        }
        else if(counter>=12)
        {
            getline(unit,storage);
            if(permanent)
            {
                permanentWeapons[x]=storage;
            }
            else if(storage=="PERMANENT")
            {
                x=-1;
                permanent=true;
            }
            else if(melee)
            {
                unitMelee[x]=storage;
            }
            else if(storage=="Melee")
            {
                melee=true;
                permanent=false;
                x=-1;
            }
            else if(!melee && !permanent && storage!="Weapons")
            {
                unitWeapons[x]=storage;

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

    ofstream results;
    results.open("Results.txt");
    if(!results)
    {
        cout<<"Error Finding Results File"<<endl;
        return -2;
    }
    results<<unitName<<endl;
    results<<"Enemy Stats"<<" /t ";
    for(int a=0;unitWeapons[a]!="";a++)
    {
        results<<unitWeapons[a]<<" /t ";
    }
    for(int a=0;unitMelee[a]!="";a++)
    {
        results<<unitMelee[a]<<" /t ";
    }
    results<<endl;
    ifstream weapon;//document holding theel weapon stats

    //declares variables to store weapon data
    string weaponName;
    int weaponStats[4]={0};
    string weaponSpecial[5]={""};
    double totalPermWeaponDamage=0;
    int totalPermWeaponPointCost=0;
    double shots=0;
    int w_strength=0;
    int AP=0;
    int damage=0;
    //loops which control the enemy stats
    for(int e_toughness=2;e_toughness<11;e_toughness++)
    {
        for(int e_sv=2;e_sv<8;e_sv++)
        {
            for(int e_inv=2;e_inv<8;e_inv++)
            {
                for(int e_wounds=1;e_wounds<11;e_wounds++)
                {
                    results<<e_toughness<<"/"<<e_sv<<"/"<<e_inv<<"/"<<e_wounds<<endl;
                    totalPermWeaponDamage=0;
                    for(int a=0;permanentWeapons[a]!="";a++)//calculates the damage for all the permanent weapons from the unit
                    {
                        for(int a=0;weaponSpecial[a]!="";a++)//clears weapon special array
                            weaponSpecial[a]="";
                        string weaponFile="./Weapons/"+permanentWeapons[a]+".txt";
                        weapon.open(weaponFile);
                        if(!weapon)
                        {
                            weaponFile="./Melee/"+permanentWeapons[a]+".txt";
                            weapon.open(weaponFile);
                            if(!weapon)
                            {
                                cout<<"Error Finding Permanent Weapon File: "<<permanentWeapons[a]<<endl;
                                return -1;
                            }
                            melee=true;
                        }
                        else
                            melee=false;
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
                        totalPermWeaponPointCost+=weaponStats[0];
                        if(!melee)//puts values into variables for ranged weapon
                        {
                            shots=weaponStats[1];
                            w_strength=weaponStats[2];
                            AP=weaponStats[3];
                            damage=weaponStats[4];
                        }
                        else
                        {
                            w_strength=weaponStats[1];
                            AP=weaponStats[2];
                            damage=weaponStats[3];
                            strength=strength+w_strength;
                        }
                        //applies special properties which only affect damage directly or the users strength
                        int attackBonus=0;
                        for(int n=0;weaponSpecial[n]!="";n++)
                        {
                            if(weaponSpecial[n]=="OneExtraAttack")
                                attackBonus=1;
                            else if(weaponSpecial[n]=="TwoExtraAttacks")
                                attackBonus=2;
                            else if(weaponSpecial[n]=="ThreeExtraAttacks")
                                attackBonus=3;
                            else if(weaponSpecial[n]=="MultiplyStrength")
                                strength=(strength-w_strength)*w_strength;//removes the additional strength given by the weapon, that was applied earlier, and instead multiplies it by the strength
                        }
                        if(damage>e_wounds)
                            damage=e_wounds;
                        if(!melee)
                        {
                            double hitPercent=hit_percent(BS,weaponSpecial);
                            double woundPercent=wound_percent(e_toughness,w_strength,weaponSpecial);
                            double savePercent=save_percent(e_sv,e_inv,AP,weaponSpecial);
                            totalPermWeaponDamage=shots*models*hitPercent*woundPercent*savePercent*damage;
                        }
                        else
                        {
                            double hitPercent=hit_percent(BS,weaponSpecial);
                            double woundPercent=wound_percent(e_toughness,strength,weaponSpecial);
                            double savePercent=save_percent(e_sv,e_inv,AP,weaponSpecial);
                            totalPermWeaponDamage=totalPermWeaponDamage+(attackBonus*models*hitPercent*woundPercent*savePercent*damage);
                        }
                    }
                    for(int a=0;unitWeapons[a]!="";a++)//calculates the damage potential of the ranged weapons
                    {
                        string weaponFile="./Weapons/"+unitWeapons[a]+".txt";
                        weapon.open(weaponFile);
                        for(int a=0;weaponSpecial[a]!="";a++)//clears weapon special array
                            weaponSpecial[a]="";
                        if(!weapon)
                        {
                            cout<<"Error Finding Weapon File: "<<unitWeapons[a]<<endl;
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
                        if(damage>e_wounds)
                            damage=e_wounds;
                        double hitPercent=hit_percent(BS,weaponSpecial);
                        double woundPercent=wound_percent(e_toughness,w_strength,weaponSpecial);
                        double savePercent=save_percent(e_sv,e_inv,AP,weaponSpecial);
                        double damageDealt=(shots*models*hitPercent*woundPercent*savePercent*damage)+totalPermWeaponDamage;
                        results<<weaponName<<endl;
                        results<<damageDealt<<endl;
                        results<<damageDealt/(pointCost+weaponPointCost+totalPermWeaponPointCost)<<endl<<endl;
                    }

                    for(int a=0;unitMelee[a]!="";a++)//calculates the damage potential of the melee weapons
                    {
                        string weaponFile="./Melee/"+unitMelee[a]+".txt";
                        weapon.open(weaponFile);
                        for(int a=0;weaponSpecial[a]!="";a++)//clears weapon special array
                            weaponSpecial[a]="";
                        if(!weapon)
                        {
                            cout<<"Error Finding Melee Weapon File: "<<unitMelee[a]<<endl;
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
                        //applies special properties which ONLY affect the final damage calculation (ie attacks, or damage modifier), and the users strength
                        int attackBonus=0;
                        strength=strength+w_strength;
                        for(int n=0;weaponSpecial[n]!="";n++)
                        {
                            if(weaponSpecial[n]=="OneExtraAttack")
                                attackBonus=1;
                            else if(weaponSpecial[n]=="TwoExtraAttacks")
                                attackBonus=2;
                            else if(weaponSpecial[n]=="ThreeExtraAttacks")
                                attackBonus=3;
                            else if(weaponSpecial[n]=="MultiplyStrength")
                                strength=(strength-w_strength)*w_strength;//removes the additional strength given by the weapon, that was applied earlier, and instead multiplies it by the strength
                        }

                        if(damage>e_wounds)
                            damage=e_wounds;
                        //finds the percentage for damage
                        double hitPercent=hit_percent(WS,weaponSpecial);
                        double woundPercent=wound_percent(e_toughness,strength,weaponSpecial);
                        double savePercent=save_percent(e_sv,e_inv,AP,weaponSpecial);
                        double damageDealt=((attacks+attackBonus)*models*hitPercent*woundPercent*savePercent*damage)+totalPermWeaponDamage;
                        results<<weaponName<<endl;
                        results<<damageDealt<<endl;
                        results<<damageDealt/(pointCost+weaponPointCost+totalPermWeaponPointCost)<<endl<<endl;
                    }
                }
            }
        }
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
    if(e_sv+AP >= 7 && e_inv_sv==7)
        return 1;
    if(((e_sv+AP)<e_inv_sv && e_inv_sv != 7) or e_inv_sv==7)
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
