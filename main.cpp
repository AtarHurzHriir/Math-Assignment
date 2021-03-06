#include <iostream>
#include <istream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

//declare functions
double hit_percent(int BS,int WS,string specialProp[3],string unitSpecial[4],string auras[3]);
double wound_percent(int e_toughness,int strength,string specialProp[3],string unitSpecial[4],string auras[3]);
double save_percent(int e_sv, int e_inv_sv,int AP,string specialProp[3],string unitSpecial[4],string auras[3]);
double bonusDamageOnWound(int e_toughness,int strength,string specialProp[3],string unitSpecial[4],string auras[3]);
int main()
{
    string unitType="";
    cout<<"Which Unit Type Would You Like to Evaluate?"<<endl;
    string units[8]={"HQ","Troop","Elite","Fast Attack","Heavy Support","Flyers","Lord of War","Dedicated Transport"};
    for(int i=0;i<8;i++)
    {
        cout<<units[i]<<", ";
    }
    cout<<endl;
    while(true)
    {
        bool valid=false;
        getline(cin,unitType);
        for(int n=0;n<8;n++)
        {
            if(unitType==units[n])
            {
                valid=true;
                break;
            }
        }
        if(valid)
            break;
        else
            cout<<"Please Enter a Valid Unit Type"<<endl;
    }
    string HQ[8]={"Chaos Lord","Chaos Lord in Terminator Armor","Daemon Prince of Nurgle","Lord of Contagion","Malignant Plaguecaster","Sorcerer","Sorcerer in Terminator Armor","Typhus"};
    string troops[9]={"Chaos Cultists","Chaos Cultists Special Weapon","Chaos Cultist Champion", "Plague Marines","Plague Marines Special Weapon","Plague Marines Melee","Plague Marine Champion","Poxwalkers","Poxwalkers with Typhus"};
    string elite[13]={"Biologus Putrifier","Blightlord Terminators","Blightlord Terminators Melee","Blightlord Terminators Special Weapon","Blightlord Terminator Champion", "Deathshroud Terminators","Deathshroud Terminator Champion", "Foul Blightspawn","Helbrute", "Noxious Blightbringer","Plague Surgeon","Possessed","Tallyman"};
    string fastAttack[8]={"Chaos Spawn (Razor Claws)","Chaos Spawn (Grasping Tseudopods)","Chaos Spawn (Toxic Haemorrage)", "Foetid Bloat-drone","Foetid Bloat-drone Degrade 1","Foetid Bloat-drone Degrade 2", "Myphitic Blight-haulers","Myphitic Blight-haulers X3"};
    string heavySupport[12]={"Chaos Land Raider","Chaos Land Raider Degrade 1","Chaos Land Raider Degrade 2","Chaos Predator","Chaos Predator Degrade 1","Chaos Predator Degrade 2","Defiler","Defiler Degrade 1","Defiler Degrade 2","Plagueburst Crawler","Plagueburst Crawler Degrade 1","Plagueburst Crawler Degrade 2"};
    string flyers[1]={""};
    string lordOfWar[3]={"Mortarion", "Mortarion Degrade 1", "Mortarion Degrade 2"};
    string dedicatedTransport[3]={"Chaos Rhino", "Chaos Rhino Degrade 1", "Chaos Rhino Degrade 2"};
    cout<<"Which Unit Would You Like to Evaluate?"<<endl;
    string desiredUnit="";
    while(true)
    {
        bool valid=false;
        if(unitType=="HQ")
        {
            if(desiredUnit=="")
            {
                for(int n=0;n<8;n++)
                {
                    cout<<HQ[n]<<", ";
                }
                cout<<endl;
            }
            else
            {
                for(int n=0;n<8;n++)
                {
                    if(desiredUnit==HQ[n])
                    {
                        valid=true;
                        break;
                    }
                }
                if(!valid)
                    cout<<"Please Enter a Valid Unit Name"<<endl;
            }
        }
        else if(unitType=="Troop")
        {
            if(desiredUnit=="")
            {
                for(int n=0;n<9;n++)
                {
                    cout<<troops[n]<<", ";
                }
                cout<<endl;
            }
            else
            {
                for(int n=0;n<9;n++)
                {
                    if(desiredUnit==troops[n])
                    {
                        valid=true;
                        break;
                    }
                }
                if(!valid)
                    cout<<"Please Enter a Valid Unit Name"<<endl;
            }
        }
        else if(unitType=="Elite")
        {
            if(desiredUnit=="")
            {
                for(int n=0;n<13;n++)
                {
                    cout<<elite[n]<<", ";
                }
                cout<<endl;
            }
            else
            {
                for(int n=0;n<13;n++)
                {
                    if(desiredUnit==elite[n])
                    {
                        valid=true;
                        break;
                    }
                }
                if(!valid)
                    cout<<"Please Enter a Valid Unit Name"<<endl;
            }
        }
        else if(unitType=="Fast Attack")
        {
            if(desiredUnit=="")
            {
                for(int n=0;n<8;n++)
                {
                    cout<<fastAttack[n]<<", ";
                }
                cout<<endl;
            }
            else
            {
                for(int n=0;n<8;n++)
                {
                    if(desiredUnit==fastAttack[n])
                    {
                        valid=true;
                        break;
                    }
                }
                if(!valid)
                    cout<<"Please Enter a Valid Unit Name"<<endl;
            }
        }
        else if(unitType=="Heavy Support")
        {
            if(desiredUnit=="")
            {
                for(int n=0;n<12;n++)
                {
                    cout<<heavySupport[n]<<", ";
                }
                cout<<endl;
            }
            else
            {
                for(int n=0;n<12;n++)
                {
                    if(desiredUnit==heavySupport[n])
                    {
                        valid=true;
                        break;
                    }
                }
                if(!valid)
                    cout<<"Please Enter a Valid Unit Name"<<endl;
            }
        }
        else if(unitType=="Flyers")
        {
            if(desiredUnit=="")
            {
                for(int n=0;n<1;n++)
                {
                    cout<<flyers[n]<<", ";
                }
                cout<<endl;
            }
            else
            {
                for(int n=0;n<1;n++)
                {
                    if(desiredUnit==flyers[n])
                    {
                        valid=true;
                        break;
                    }
                }
                if(!valid)
                    cout<<"Please Enter a Valid Unit Name"<<endl;
            }
        }
        else if(unitType=="Lord of War")
        {
            if(desiredUnit=="")
            {
                for(int n=0;n<3;n++)
                {
                    cout<<lordOfWar[n]<<", ";
                }
                cout<<endl;
            }
            else
            {
                for(int n=0;n<3;n++)
                {
                    if(desiredUnit==lordOfWar[n])
                    {
                        valid=true;
                        break;
                    }
                }
                if(!valid)
                    cout<<"Please Enter a Valid Unit Name"<<endl;
            }
        }
        else if(unitType=="Dedicated Transport")
        {
            if(desiredUnit=="")
            {
                for(int n=0;n<3;n++)
                {
                    cout<<dedicatedTransport[n]<<", ";
                }
                cout<<endl;
            }
            else
            {
                for(int n=0;n<3;n++)
                {
                    if(desiredUnit==dedicatedTransport[n])
                    {
                        valid=true;
                        break;
                    }
                }
                if(!valid)
                    cout<<"Please Enter a Valid Unit Name"<<endl;
            }
        }
        if(valid)
            break;
        getline(cin,desiredUnit);
    }
    cout<<"Would you like to add any aura abilities?"<<endl;
    string answer="";
    cin>>answer;
    string auras[3]={""};
    if(answer=="Yes")
    {
        cout<<"What ability would you like to add?"<<endl;
        string storage="";
        int i=0;
        while(true)
        {
            cin>>storage;
            if(storage=="RerollFightHit")
            {
                auras[i]="RerollFightHit";
                cout<<"OK!"<<endl;
                i++;
            }
            else if(storage=="ArchContaminator")
            {
                auras[i]="ArchContaminator";
                cout<<"OK!"<<endl;
                i++;
            }
            else if(storage=="RerollHitOne")
            {
                auras[i]="RerollHitOne";
                cout<<"OK!"<<endl;
                i++;
            }
            else if(storage=="End")
                break;
        }
    }
    ifstream unit;//document holding the units stats
    int counter=0;
    double unitStats[11];//array storing all of the units stats
    string unitSpecial[4]={""};//array for storing the special abilities of the unit
    string unitName = "None";//variable storing units name
    string unitFileDirectory="./Units/"+unitType+"/"+desiredUnit+".txt";
    unit.open(unitFileDirectory);
    if(!unit)
    {
        cout<<"Error File Not Found"<<endl;
        return -1;
    }
    string storage="None";//storage variable to determine when the melee weapon list starts
    bool melee=false;//determines where the melee weapon list begins
    vector<string> unitWeapons; //declares the vector to store the ranged weapons
    vector<string> unitMelee;//declares the array to store the melee weapons
    vector<string> permanentWeapons;//declares an array to store any ranged weapons that cannot be switched out
    bool permanent=false;//variable to check if there are any weapons that cannot be switched out
    bool special=false;//variable to check if there are any special abilities
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
            int x=0;
            getline(unit,storage);
            if(special)
            {
                unitSpecial[x]=storage;
                x++;
            }
            else if (storage=="Special")
            {
                special=true;
            }
            else if(permanent)
            {
                permanentWeapons.push_back(storage);
            }
            else if(storage=="PERMANENT")
            {
                permanent=true;
            }
            else if(melee)
            {
                unitMelee.push_back(storage);
            }
            else if(storage=="Melee")
            {
                melee=true;
                permanent=false;
            }
            else if(!melee && !permanent && storage!="Weapons")
            {
                unitWeapons.push_back(storage);
            }
        }
        counter++;
    }
    unitWeapons.erase(unitWeapons.begin());
    cout<<"Weapons Obtained"<<endl;
    unit.close();
    //Puts the unitStats array into variables for easier use
    int models=unitStats[0];
    //bool champion=unitStats[1];
    int pointCost=unitStats[2];
    int WS=unitStats[3];
    int BS=unitStats[4];
    int unit_strength=unitStats[5];
    int toughness=unitStats[6];
    int wounds=unitStats[7];
    double unit_attacks=unitStats[8];
    int sv=unitStats[9];
    int inv_sv=unitStats[10];
    ofstream damageOutputFile;
    damageOutputFile.open("Average Damage of Unit.csv");
    if(!damageOutputFile)
    {
        cout<<"Error Finding Average Damage of Unit File"<<endl;
        return -2;
    }
    ofstream damagePerPoint;
    damagePerPoint.open("Damage Per Point.csv");
    if(!damagePerPoint)
    {
        cout<<"Error Finding Average Damage of Unit File"<<endl;
        return -2;
    }
    damageOutputFile<<","<<unitName<<endl;
    damageOutputFile<<"Enemy Stats (T/SV/INV/W),";
    damagePerPoint<<","<<unitName<<endl;
    damagePerPoint<<"Enemy Stats (T/SV/INV/W),";
    for(int a=0;a<unitWeapons.size();a++)
    {
        damageOutputFile<<unitWeapons[a]<<",";
        damagePerPoint<<unitWeapons[a]<<",";
    }
    for(int a=0;a<unitMelee.size();a++)
    {
        damageOutputFile<<unitMelee[a]<<",";
        damagePerPoint<<unitMelee[a]<<",";
    }
    damageOutputFile<<endl;
    damagePerPoint<<endl;
    ifstream weapon;//document holding theel weapon stats
    //declares variables to store weapon data
    string weaponName;
    double weaponStats[5]={0.0};
    string weaponSpecial[4]={""};
    double totalPermWeaponDamage=0;
    int totalPermWeaponPointCost=0;

    //loops which control the enemy stats
    for(int e_toughness=2;e_toughness<=10;e_toughness++)
    {
        if(e_toughness>2)
            cout<<"Toughness "<<e_toughness-1<<" complete"<<endl;
        cout<<"Toughness "<<e_toughness<<" starting"<<endl;
        for(int e_sv=2;e_sv<8;e_sv++)
        {
            for(int e_inv=2;e_inv<8;e_inv++)
            {
                for(int e_wounds=1;e_wounds<=5;e_wounds++)
                {
                    damageOutputFile<<e_toughness<<"/"<<e_sv<<"/"<<e_inv<<"/"<<e_wounds<<",";
                    damagePerPoint<<e_toughness<<"/"<<e_sv<<"/"<<e_inv<<"/"<<e_wounds<<",";
                    totalPermWeaponDamage=0;

                    for(int a=0;a<permanentWeapons.size();a++)//calculates the damage for all the permanent weapons from the unit
                    {
                        int strength=unit_strength;
                        int attacks=unit_attacks;
                        double shots=0;
                        double w_strength=0;
                        int AP=0;
                        double damage=0;
                        for(int i=0;weaponSpecial[i]!="";i++)
                        {
                            weaponSpecial[i]="";
                        }
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
                        totalPermWeaponPointCost+=weaponStats[0]*models;
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
                        {
                            damage=e_wounds;
                        }
                        if(!melee)
                        {
                            double hitPercent=hit_percent(BS,7,weaponSpecial,unitSpecial,auras);
                            double woundPercent=wound_percent(e_toughness,w_strength,weaponSpecial,unitSpecial,auras);
                            double savePercent=save_percent(e_sv,e_inv,AP,weaponSpecial,unitSpecial,auras);
                            totalPermWeaponDamage=shots*models*hitPercent*woundPercent*savePercent*damage;
                        }
                        else
                        {
                            double hitPercent=hit_percent(7,WS,weaponSpecial,unitSpecial,auras);
                            double woundPercent=wound_percent(e_toughness,strength,weaponSpecial,unitSpecial,auras);
                            double savePercent=save_percent(e_sv,e_inv,AP,weaponSpecial,unitSpecial,auras);
                            totalPermWeaponDamage=totalPermWeaponDamage+(attackBonus*hitPercent*woundPercent*savePercent*damage)*models;
                        }
                    }
                    for(int a=0;a<unitWeapons.size();a++)//calculates the damage potential of the ranged weapons
                    {
                        string weaponFile="./Weapons/"+unitWeapons[a]+".txt";
                        weapon.open(weaponFile);
                        for(int i=0;weaponSpecial[i]!="";i++)
                        {
                            weaponSpecial[i]="";
                        }
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
                            else if(counter <6)
                            {
                                weapon>>weaponStats[counter-1];//gets the stats of the unit
                            }
                            else
                            {
                                weapon>>weaponSpecial[counter-6];
                            }
                            counter++;
                        }
                        weapon.close();
                        //puts weapon values into useable variables
                        int weaponPointCost=weaponStats[0]*models;
                        double shots=weaponStats[1];
                        double w_strength=weaponStats[2];
                        int AP=weaponStats[3];
                        double damage=weaponStats[4];
                        double bonusDamage=0.0;
                        for(int n=0;auras[n]!="";n++)
                        {
                            if(auras[n]=="ArchContaminator")
                            {
                                for(int i=0;weaponSpecial[i]!="";i++)
                                {
                                    if(weaponSpecial[i]=="PlagueWeapon")
                                        weaponSpecial[i]=="RerollWound";
                                }
                            }
                        }
                        for(int n=0;unitSpecial[n]!="";n++)
                        {
                            if(unitSpecial[n]=="BlightRacks" && weaponName=="Hyper Blight Grenade")
                            {
                                w_strength+=1;
                                damage+=1;
                                bonusDamage+=hit_percent(BS,7,weaponSpecial,unitSpecial,auras)*bonusDamageOnWound(e_toughness,w_strength,weaponSpecial,unitSpecial,auras);
                            }
                            else if(unitSpecial[n]=="ToxicPresence")
                            {
                                e_toughness-=1;
                            }
                            else if(unitSpecial[n]=="Psycker")
                            {
                                bonusDamage+=(5.0/12.0*2)+(2.0/12.0*3.5);
                            }
                            else if(unitSpecial[n]=="Pestilential Fallout")
                            {
                                bonusDamage+=(7.0/12.0);
                            }
                        }
                        for(int n=0;weaponSpecial[n]!="";n++)
                        {
                            if(weaponSpecial[n]=="UserStrength")
                                w_strength=unit_strength;
                            else if(weaponSpecial[n]=="Combi")
                            {
                                string blah[5]={"MinusOneToHit","","","",""};
                                bonusDamage+=hit_percent(BS,7,blah,unitSpecial,auras)*wound_percent(e_toughness,4,blah,unitSpecial,auras)*save_percent(e_sv,e_inv,0,blah,unitSpecial,auras);
                            }
                            else if(weaponSpecial[n]=="HCombi")
                            {
                                string blah[5]={"MinusOneToHit","","","",""};
                                bonusDamage+=2*hit_percent(BS,7,blah,unitSpecial,auras)*wound_percent(e_toughness,4,blah,unitSpecial,auras)*save_percent(e_sv,e_inv,0,blah,unitSpecial,auras);
                            }
                            else if(weaponSpecial[n]=="Grenade")
                                shots=shots/models;//makes it so only one model uses the weapon
                        }
                        //finds the percentage for damage
                        if(damage>e_wounds)
                        {
                            damage=e_wounds;
                        }
                        double hitPercent=hit_percent(BS,7,weaponSpecial,unitSpecial,auras);
                        double woundPercent=wound_percent(e_toughness,w_strength,weaponSpecial,unitSpecial,auras);
                        double savePercent=save_percent(e_sv,e_inv,AP,weaponSpecial,unitSpecial,auras);
                        double damageDealt=(shots*models*hitPercent*woundPercent*savePercent*damage)+totalPermWeaponDamage+bonusDamage;
                        damageOutputFile<<fixed<<damageDealt<<",";
                        damagePerPoint<<fixed<<damageDealt/(pointCost+weaponPointCost+totalPermWeaponPointCost)<<",";
                        for(int n=0;unitSpecial[n]!="";n++)
                        {
                            if(unitSpecial[n]=="ToxicPresence")
                            {
                                e_toughness+=1;
                            }
                        }
                    }
                    for(int a=0;a<unitMelee.size();a++)//calculates the damage potential of the melee weapons
                    {
                        int strength=unit_strength;
                        double attacks=unit_attacks;
                        string weaponFile="./Melee/"+unitMelee[a]+".txt";
                        weapon.open(weaponFile);
                        for(int i=0;weaponSpecial[i]!="";i++)
                        {
                            weaponSpecial[i]="";
                        }
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
                        int weaponPointCost=weaponStats[0]*models;
                        double w_strength=weaponStats[1];
                        int AP=weaponStats[2];
                        double damage=weaponStats[3];
                        //applies special properties which ONLY affect the final damage calculation (ie attacks, or damage modifier), and the users strength
                        double attackBonus=0.0;
                        double bonusDamage=0.0;
                        double mortalWoundDamage=0.0;
                        bool carryOver=false;
                        strength=strength+w_strength;
                        for(int n=0;auras[n]!="";n++)
                        {
                            if(auras[n]=="ArchContaminator")
                            {
                                for(int i=0;weaponSpecial[i]!="";i++)
                                {
                                    if(weaponSpecial[i]=="PlagueWeapon")
                                        weaponSpecial[i]=="RerollWound";
                                }
                            }
                        }
                        for(int n=0;weaponSpecial[n]!="";n++)
                        {
                            if(weaponSpecial[n]=="OneExtraAttack")
                                attackBonus=1.0;
                            else if(weaponSpecial[n]=="TwoExtraAttacks")
                                attackBonus=2.0;
                            else if(weaponSpecial[n]=="ThreeExtraAttacks")
                                attackBonus=3.0;
                            else if(weaponSpecial[n]=="ThreePointFiveExtraAttacks")
                                attackBonus=3.5;
                            else if(weaponSpecial[n]=="SixExtraAttacks")
                                attackBonus=6.0;
                            else if(weaponSpecial[n]=="TwoTimesAttack")
                                attacks=attacks*2;
                            else if(weaponSpecial[n]=="ThreeTimesAttack")
                                attacks=attacks*3;
                            else if(weaponSpecial[n]=="MultiplyStrength")
                                strength=(strength-w_strength)*w_strength;//removes the additional strength given by the weapon, that was applied earlier, and instead multiplies it by the strength
                            else if(weaponSpecial[n]=="ReplaceStrength")
                                strength=w_strength;
                            else if(weaponSpecial[n]=="MortalWoundOnWound6")
                                mortalWoundDamage+=bonusDamageOnWound(e_toughness,strength,weaponSpecial,unitSpecial,auras);
                            else if(weaponSpecial[n]=="CarryOverDamage")
                                carryOver=true;
                        }
                        for(int n=0;unitSpecial[n]!="";n++)
                        {
                            if(unitSpecial[n]=="NurglesGift")
                            {
                                bonusDamage+=0.5;
                            }
                            else if(unitSpecial[n]=="ToxicPresence")
                            {
                                e_toughness-=1;
                            }
                            else if(unitSpecial[n]=="HostOfPlagues4")
                            {
                                bonusDamage+=1.0;
                            }
                            else if(unitSpecial[n]=="HostOfPlagues5")
                            {
                                bonusDamage+=2/3;
                            }
                            else if(unitSpecial[n]=="HostOfPlagues6")
                            {
                                bonusDamage+=1/3;
                            }
                            else if(unitSpecial[n]=="Psycker")
                            {
                                bonusDamage+=(17.0/12.0);
                            }
                            else if(unitSpecial[n]=="Pestilential Fallout")
                            {
                                bonusDamage+=(7.0/12.0);
                            }
                            else if(unitSpecial[n]=="AuraOfRust")
                            {
                                double d=damage;
                                if(d>e_wounds && !carryOver)
                                    d=e_wounds;
                                bonusDamage+=d*attacks*models*hit_percent(7,WS,weaponSpecial,unitSpecial,auras)*1/6*save_percent(e_sv,e_inv,AP+1,weaponSpecial,unitSpecial,auras);
                            }
                        }
                        if(damage>e_wounds && !carryOver)
                        {
                            damage=e_wounds;
                        }
                        //finds the percentage for damage
                        double hitPercent=hit_percent(7,WS,weaponSpecial,unitSpecial,auras);
                        double woundPercent=wound_percent(e_toughness,strength,weaponSpecial,unitSpecial,auras);
                        double savePercent=save_percent(e_sv,e_inv,AP,weaponSpecial,unitSpecial,auras);
                        double damageDealt=((attacks+attackBonus)*models*hitPercent*woundPercent*savePercent*damage+((attacks+attackBonus)*mortalWoundDamage*hitPercent*models))+totalPermWeaponDamage+bonusDamage;
                        damageOutputFile<<fixed<<damageDealt<<",";
                        damagePerPoint<<fixed<<damageDealt/(pointCost+weaponPointCost+totalPermWeaponPointCost)<<",";
                        for(int n=0;unitSpecial[n]!="";n++)
                        {
                            if(unitSpecial[n]=="ToxicPresence")
                            {
                                e_toughness+=1;
                            }
                        }
                    }
                    damageOutputFile<<endl;
                    damagePerPoint<<endl;
                }
            }
        }
    }
    cout<<"Calculations Complete"<<endl;
    return 0;
}

double hit_percent(int BS,int WS,string specialProp[3],string unitSpecial[4],string auras[3])
{
    for(int n=0;specialProp[n]!="";n++)
    {
        if(specialProp[n]=="MinusOneToHit")
        {
            BS+=1;
            WS+=1;
        }
        else if(specialProp[n]=="AlwaysHitFive")
            BS=5;
        else if(specialProp[n]=="Combi" or specialProp[n]=="HCombi")
            BS+=1;
        else if(specialProp[n]=="Auto")
            return 1;
    }
    double hit=0.0;
    if(WS>=7 && BS>=7)
        return 0;
    else if(WS>=7)
        hit=(7.0-BS)/6.0;
    else
        hit=(7.0-WS)/6.0;
    for(int n=0;unitSpecial[n]!="" or auras[n]!="";n++)
    {
        if(unitSpecial[n]=="RerollHitOne" or auras[n]=="RerollHitOne")
        {
            hit=hit+((1/((1-hit)*6))*hit);
        }
        else if((unitSpecial[n]=="RerollFightHit" or auras[n]=="RerollFightHit")&& BS==7)
        {
            hit=hit+(hit*(1-hit));
        }
    }
    return hit;
}
double wound_percent(int e_toughness, int strength,string specialProp[3],string unitSpecial[4],string auras[3])
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
    for(int n=0;unitSpecial[n]!="";n++)
    {
        if(unitSpecial[n]=="AuraOfRust")
            percent-=1/6;
    }
    for(int n=0;specialProp[n]!="";n++)
    {
        if(specialProp[n]=="PlagueWeapon")
            percent=percent+((1/((1-percent)*6))*percent);
        else if(specialProp[n]=="RerollWound")
            percent=percent+(percent*(1-percent));
    }
    return percent;
}

double save_percent(int e_sv, int e_inv_sv, int AP,string specialProp[3],string unitSpecial[4],string auras[3])
{
    double save=0.0;
    if(e_sv+AP >= 7 && e_inv_sv==7)
        return 1;
    else if((e_sv+AP)<e_inv_sv)
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
    return save;
}

double bonusDamageOnWound(int e_toughness,int strength,string specialProp[3],string unitSpecial[4],string auras[3])
{
    double damage=1.0/6.0;
    double percent=0.0;
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
    for(int n=0;specialProp[n]!="";n++)
    {
        if(specialProp[n]=="PlagueWeapon")
            damage=damage+((1/((1-percent)*6))*(1.0/6.0));
        else if(specialProp[n]=="RerollWound")
            damage=damage+((1-percent)*1.0/6.0);
    }
    return damage;
}
