/*
Надо разработать упрощённую модель умного дома для дачи.
Есть несколько датчиков:
+датчик температуры снаружи,
+датчик температуры внутри дома.

В доме расположен электронный “умный” щиток с автоматами. Каждый автомат отвечает за включение и отключение определённых устройств или групп устройств.
+Первый автомат - это отключение и включение питания всего дома,
+второй - основные розетки дома,
+третий - свет внутри дома,
+четвёртый - наружный свет в саду,
+пятый - отопление в помещении,
+шестой - отопление водопровода идущего из скважины с насосом,
+седьмой - кондиционер в помещении.

Есть несколько условий по включению/отключению техники в доме и вне его.

+ Как только температура снаружи падает ниже 0, надо включить систему обогрева водопровода и отключить её, если температура снаружи поднялась выше 5 градусов.

+Если на дворе вечер (время больше 16:00 и меньше 5:00 утра) и снаружи есть какое-то движение, то необходимо включить садовое освещение.
+Если движения нет или время не вечернее - света снаружи быть не должно.

+При условии, что температура в помещении упала ниже 22 градусов, должно включится отопление. Как только температура поднимается выше или равно 25-и градусам,
+отопление автоматически отключается.

+Если температура в помещении поднялась до 30 градусов, включается кондиционер. Как только температура становится 25 градусов - кондиционер отключается.

+Всё освещение в доме также “умное” и поддерживает настройку цветовой температуры для комфортного нахождения. Каждый день начиная с 16:00 и до 20:00,
+температура цвета должна плавно изменяться с 5000K до 2700К. Разумеется, это изменение должно происходить в случае, если свет сейчас включен.
+В 0:00 температура сбрасывается до 5000К.

Все события по отключению и включению устройств должны выводится в консоль явным образом. Если устройство не изменило своего состояния 
(осталось включенным или выключенным) события генерироваться не должно! Если свет в доме включен, должна отображаться текущая цветовая температура.

Программа выполняется следующим образом.
Каждый час пользователь сообщает состояние всех основных датчиков и света:
температура снаружи, 
температура внутри,
есть ли движение снаружи,
включен ли свет в доме.
Данные параметры вводятся разом в одну строку, через пробел, а потом парсятся в переменные из строкового буфера stringstream.
Информация о движении выводится в формате yes/no. 
Включение и отключение света происходит с помощью on/off. Стартовое время для симуляции умного дома - это 0:00. 
Требуется осуществить симуляцию на протяжении двух дней.
*/

#include <iostream>
#include <string>
using namespace std;
//ligt temperature program     
int LightHours (int nTime)
{
    if (nTime > 20 && nTime < 24) nTime = 20;
    if (nTime > 15 && nTime < 24) return 2700 + (5000 - 2700) / (21 - nTime);
    else return 5000;
}
//electrical circit break swiches
enum io
{   
    //outputs
    MAIN_POWER = 1,     //main power in home
    ELECT_SOCKET = 2,   //electrical socket in the house
    LIGHT_HOUSE = 4,    //light in the house
    LIGHT_GARDEN = 8,   //light in the garden
    HEAT_HOME = 16,     //heating home
    HEAT_PIPE = 32,     //heating water pipe
    CONDITIONER = 64,   //air conditioning in the home
    //inputs
    MOVE_GARDEN = 128   //move in the garden
};

int main()
{
 /*     bCircBreak1 = 0,    //main power home
        bCircBreak2 = 0,    //electrical sockets in the house
        bCircBreak3 = 0,    //light in the house
        bCircBreak4 = 0,    //light in the garden
        bCircBreak5 = 0,    //heating home
        bCircBreak6 = 0,    //heating water pipe
        bCircBreak7 = 0;    //air conditioning in the home
 */
    
    int nHoursCount = 0,    //hours
        nTime = 0,          //clock
        nState = 0;         //variable for io

    while (nHoursCount < 48)
    {
        enum change
        {
            //outputs
            CH_MAIN_POWER = 1,     //main power in home
            CH_ELECT_SOCKET = 2,   //electrical socket in the house
            CH_LIGHT_HOUSE = 4,    //light in the house
            CH_LIGHT_GARDEN = 8,   //light in the garden
            CH_HEAT_HOME = 16,     //heating home
            CH_HEAT_PIPE = 32,     //heating water pipe
            CH_CONDITIONER = 64,   //air conditioning in the home
            //inputs
            CH_MOVE_GARDEN = 128   //move in the garden
        };
        int nChange = 0;

        string sInput;

        //status query
        cout << "Input condition: " << endl
            << "<temp outside> <temp inside> <move outside, yes/no> <light inside, on/off>" << endl;
        getline(cin, sInput);

        //splint input text into separate variable 
        string sConditionTempOut, sConditionTempHome, sConditionMove, sConditionLightHome;

        for (int n = 0, nCountWords = 0; n < sInput.size(); n++)
        {
            switch (nCountWords)
            {
            case 0:
                if (sInput[n] != ' ')
                {
                    sConditionTempOut += sInput[n];
                    break;
                }
                else
                {
                    ++nCountWords;
                    break;
                }
            case 1:
                if (sInput[n] != ' ')
                {
                    sConditionTempHome += sInput[n];
                    break;
                }
                else
                {
                    ++nCountWords;
                    break;
                }
            case 2:
                if (sInput[n] != ' ')
                {
                    sConditionMove += sInput[n];
                    break;
                }
                else
                {
                    ++nCountWords;
                    break;
                }
            case 3:
                if (sInput[n] != ' ')
                {
                    sConditionLightHome += sInput[n];
                    break;
                }
                else
                {
                    ++nCountWords;
                    break;
                }
            }


        }

        //parsing input variables
        float   fTempOutside = stof(sConditionTempOut),
            fTempInside = stof(sConditionTempHome);

        if (sConditionMove == "yes" && !(nState & MOVE_GARDEN))
        {
            nState |= MOVE_GARDEN;
            nChange |= CH_MOVE_GARDEN;
        }  
        else if (sConditionMove == "no" && nState & MOVE_GARDEN)
        {
            nState &= ~MOVE_GARDEN;
            nChange |= CH_MOVE_GARDEN;
        }

        if (sConditionLightHome == "on" && !(nState & LIGHT_HOUSE))
        {
            nState |= LIGHT_HOUSE;
            nChange |= CH_LIGHT_HOUSE;
        }   
        else if (sConditionLightHome == "off" && nState & LIGHT_HOUSE)
        {
            nState &= ~LIGHT_HOUSE; 
            nChange |= CH_LIGHT_HOUSE;
        }

        //Heating waterpipe program
        if (fTempOutside < 0 && !(nState & HEAT_PIPE))
        {
            nState |= HEAT_PIPE;
            nChange |= CH_HEAT_PIPE;
        }
        else if (fTempOutside > 5 && nState & HEAT_PIPE)
        {
            nState &= ~HEAT_PIPE; 
            nChange |= CH_HEAT_PIPE;
        }

        //outside light program 16:00 - 5:00     
        if ((nTime > 15 || nTime < 6) && nState & MOVE_GARDEN && nState & !(LIGHT_GARDEN)) 
        {
            nState |= LIGHT_GARDEN;
            nChange |= CH_LIGHT_GARDEN;
        }
        else if ((nTime > 5 && nTime < 16 || !(nState & MOVE_GARDEN)) && nState & LIGHT_GARDEN)
        {
            nState &= ~LIGHT_GARDEN;
            nChange |= CH_LIGHT_GARDEN;
        }
                
        //heating program
        if (fTempInside < 22.001f && !(nState & HEAT_HOME)) 
        {
            nState |= HEAT_HOME;
            nChange |= HEAT_HOME;
        }
        else if (fTempInside > 25.001f && nState & HEAT_HOME) 
        {
            nState &= ~HEAT_HOME; 
            nChange |= HEAT_HOME;
        }
    
        //cooling program
        if (fTempInside > 30.001f && !(nState & CONDITIONER)) 
        {
            nState |= CONDITIONER;
            nChange |= CONDITIONER;
        }
        else if (fTempInside < 25.001f && nState & CONDITIONER) 
        {
            nState &= ~CONDITIONER; 
            nChange |= CONDITIONER;
        }
      
        cout << "Time: " << nTime << ":00" << endl;
        if (nState & MAIN_POWER && nChange & CH_MAIN_POWER) cout << "Main power is on" << endl;
        else if (!(nState & MAIN_POWER) && nChange & CH_MAIN_POWER) cout << "Main power is off" << endl;
       
        if (nState & ELECT_SOCKET && nChange & CH_ELECT_SOCKET) cout << "Electric socket is on" << endl;
        else if (!(nState & ELECT_SOCKET) && nChange & CH_ELECT_SOCKET) cout << "Electric socket is off" << endl;
        
        int nTempLight = LightHours(nTime);     //ligt temperature in home
        if (nState& LIGHT_HOUSE && nChange & CH_LIGHT_HOUSE) cout << "Lighting in the house is on. Light temperature: " << nTempLight << "K" << endl;
        else if (!(nState & LIGHT_HOUSE) && nChange & CH_LIGHT_HOUSE) cout << "Lighting in the house is off" << endl;
        
        if (nState & LIGHT_GARDEN && nChange & CH_LIGHT_GARDEN) cout << "Lighting in the garden is on" << endl;
        else if (!(nState & LIGHT_GARDEN) && nChange & CH_LIGHT_GARDEN) cout << "Lighting in the garden is off" << endl;
        
        if (nState & HEAT_HOME && nChange & CH_HEAT_HOME) cout << "Heating home is on" << endl;
        else if (!(nState & HEAT_HOME) && nChange & CH_HEAT_HOME) cout << "Heating home is off" << endl;
        
        if (nState & HEAT_PIPE && nChange & CH_HEAT_PIPE) cout << "Heating pipe is on" << endl;
        else if (!(nState & HEAT_PIPE) && nChange & CH_HEAT_PIPE) cout << "Heating pipe is off" << endl;
        
        if (nState & CONDITIONER && nChange & CH_CONDITIONER) cout << "Conditionering home is on" << endl;
        else if (!(nState & CONDITIONER) && nChange & CH_CONDITIONER) cout << "Conditionering home is off" << endl;
        cout << "-----------------------------" << endl;



        nHoursCount++;
        nTime++;
        if (nHoursCount == 24) nTime = 0;
    }
    
}
