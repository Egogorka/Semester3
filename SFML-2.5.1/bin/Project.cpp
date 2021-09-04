#include <SFML/Graphics.hpp>
#include <chrono>
#include<ctime>
#include <fstream>
# include <random>
#include <iostream>
#include <cmath>
#include <vector>
#include <iostream>
#include <sstream>

using namespace sf;
using namespace std;

const int H = 500; //
const int L = 500; //
const int N = 3;
const int r = 15;
const int G_up = 70;
const int G_down = 40;
const int G_left = 70;
const float delay = 0.1;
const int tr_r = 10;


class Key
{
    public:
    int x;
    int y;
};

class Rocket
{

public:
    int x;
    int y;
    int damage;

};

class Barrier
{

public:
    int x;// ���������� ������ ����
    int y;
    int* arr;
    int dx; // ����� ��������������
    int dy; // ������ ��������������

    Barrier(int inx, int iny, int indx,int indy) // �����������
     {
        x = inx;
        y = iny;
        dx = indx;
        dy = indy;
    }

};

class Square
{
public:

        int x; // ���������� ������� ��������
        int y;
        int r;// ������ ��������� ����������
        int vx;
        int vy;
        int health;
        int g_down;
        int g_left;
        int g_up;

        void movement ()
        {
            vx += g_left * delay;
            vy += g_down * delay;
            y += vy * delay + g_down * delay* delay/2;
            x -= vx * delay + g_left * delay* delay/2;
        }

        void recover (int Gas_x, int Gas_y)
        {
            int dx = abs (Gas_x - x);
            int dy = abs (Gas_y - y);
            if (dx < r && dy < r) health += 10;

        }

        void Bar_interaction (int check, Barrier v)
        {
            int y1 = (y + vy * delay + g_down * delay* delay/2 ); // ���������� ������ ����;
            int x1 = x - vx * delay + g_left * delay* delay/2;
                if (check == 0 )
                    {
                            if ( y1 > v.y and x < v.x +  v.dx  and x > v.x   and  y1 < v.y  + v.dy)
                        {
                            vy = 0;
                            g_down = 0;


                        }
                        else g_down = G_down;
                    }


                    if (check == 1)
                    {

                        if (x1 < v.x + v.dx  and  y1 < v.y + v.dy and y1 > v.y)
                        {
                            vx = 0;
                            g_left = 0;

                        }

                        else g_left = G_left;

                    }

                    if (check == 2)
                    {

                        if ( y1 > v.y and x < v.x +  v.dx  and x > v.x   and  y1 < v.y  + v.dy)
                        {
                            vy = 0;
                            g_down = 0;


                        }
                        else g_down = -G_down;

                    }


        }

        int Key_interaction( Key k, int check )
        {
                    float dx = (k.x -  tr_r  - x + r);
                    float dy = (k.y -  tr_r  - y + r) ;
                    if ((dx*dx + dy*dy) < 1600)
                    {

                        health -= 10;

                    }


                    if (abs(dx)  < 5 && abs(dy) < 5) // ������������ ���������
                    {
                        vx = 0;
                        vy = 0;
                        check ++;
                    }
            return check;
        }

};


class Gas
{
  public:
        int x;
        int y;
        int vx;
        int vy;
    void create ()
    {
        x = rand()%L +50;
        y = rand()%H + 50 ;
        vx = rand()%200;
        vy = rand()%200;

    }

    void movement()
    {


    }

};

class Field
{




};
int main()
{
    sf::Font font;// ����� ������
    font.loadFromFile("CyrilicOld.TTF");


    int check = -1; // ����� ����


    srand(time(NULL));
    RenderWindow window(VideoMode(H,L), "Movement");





    vector<Key>  keys;

    int g = 10;
    Key element;


    element.x = L - 50;
    element.y = 50;
    keys.push_back(element);

    element.x = 50 ;
    element.y = H - 50;
    keys.push_back(element);

    element.x = L/2;
    element.y = H/2;
    keys.push_back(element);



    Gas* mass = new Gas[N];
    //Barrier* mass_of_bar = new Barrier[4];
    vector<Barrier> v;

    Square object;
    object.r = 10;
    object.health = 1000;
    object.x = 100 ;
    object.y = 100;
    object.vy = -40;
    object.g_up = 0; // ������� ��������� ����
    object.g_down = G_down;
    object.g_left = 0;



    for (int i = 0; i < N; i++ )
    {

        mass[i].create();
        /*
        (mass + i)->x = rand()%L +50;
        (mass + i)->y = rand()%H + 50 ;
        mass[i].vx = rand()%200;
        mass[i].vy = rand()%200;
        */
    }


    // ���������� ��� ������� � ��������
	float timer = 0 ; //, delay = 0.1;

	// ���� (������)
	Clock clock;


    while(window.isOpen())
    {

        if (check == -1)
        {
            window.clear(Color:: White);
            int R = 40;
            int Button_x = L/2 - R;
            int Button_y = H/2 + R;

            CircleShape circle5(R, 4);
            circle5.setFillColor(Color(230, 0, 230));
            circle5.move(Button_x, Button_y);
            window.draw(circle5);


        Text text1;
        text1.setFont(font);
        text1.setCharacterSize(20);
        text1.setFillColor(sf::Color::Blue);


        text1.setString("������� ������� �� ��������������! ");
        text1.setPosition (L/4  , H/4);
        window.draw(text1);



            Event event1;
            while (window.pollEvent(event1))
            {
                if (event1.type == Event::Closed) window.close();
                if (event1.type == sf::Event::MouseButtonPressed)
                {
                    if (event1.mouseButton.button == sf::Mouse::Left)
                    {
                        int Mouse_x = event1.mouseButton.x;
                        int Mouse_y = event1.mouseButton.y;
                        if ( Mouse_x < Button_x + 2*R and  Mouse_x > Button_x and Mouse_y > Button_y and  Mouse_y < Button_y + R* 2)
                        {
                            check ++;
                        }


                    }
                }


            }


        }


        if (check >= 0 and check < 3)
        {



            float time = clock.getElapsedTime().asSeconds();
            clock.restart();
            timer += time;


            Event event;


        if (object.health > 0 )
        {


            while (window.pollEvent(event))
            {



                if (event.type == Event::Closed) window.close();
                //if (object.health < 0) window.close();
                if (event.key.code == Keyboard::Up)
                {
                    if (check == 0)// ���������� ����
                    {
                        object.vy = -80;
                        object.g_down = G_down;
                    }

                    if (check == 1 or check == 2) // ���������� ����� � �����
                    {
                        object.y -= 2;

                    }

                }

                if (event.key.code == Keyboard::Down)
                {



                    if (check == 0 or check == 1) object.y += 2; // ���������� ���� � �����
                    if (check == 2) // ���������� �����
                    {
                        object.vy = 80;
                        object.g_down = - G_down;
                    }

                }

                if (event.key.code == Keyboard::Left) object.x -= 2;
                if (event.key.code == Keyboard::Right)
                {
                    if (check == 0 ) object.x += 2; // ���������� ���� � �����
                    if (check == 2) object.x += 2;
                    if (check == 1)
                    {
                        object.vx = -80;
                        object.g_left = G_left;

                    }

                }


                if (event.key.code == Keyboard::W)
                {
                    Barrier bar_up{object.x + r - 25 ,0  , 50, object.y }; // x, y, dx, dy  object.x - ������� ����� ����
                    v.push_back(bar_up);
                }



                if (event.key.code == Keyboard::D)
                {
                    Barrier bar_up{object.x + 2* object.r , object.y + object.r - 25 , 4,50}; // x, y, dx, dy
                    v.push_back(bar_up);
                }

                 if (event.key.code == Keyboard::S)
                {
                    Barrier bar_up{object.x + r - 25 , object.y + 2*object.r  , 50, H - object.y}; // x, y, dx, dy  object.x - ������� ����� ����
                    v.push_back(bar_up);
                }



                if (event.key.code == Keyboard::A)
                {
                    Barrier bar_up{0, object.y + r - 25  , object.x - 2*object.r ,50}; // x, y, dx, dy
                    v.push_back(bar_up);
                }

            }





            if (timer > delay )
            {

                // �������� �����
                for (int i = 0; i < N; i++)
                {


                    if ((mass[i].x  + r)>= L  or (mass[i].x - r) <= 10)
                    {
                        mass[i].vx = - mass[i].vx ;
                        mass[i].x += mass[i].vx * delay;

                    }
                    if ((mass[i].y + r) >= H   or (mass[i].y  - r) <= 10)
                    {

                        mass[i].vy = - mass[i].vy ;
                        mass[i].y += mass[i].vy * delay;

                    }



                    object.recover(mass[i].x, mass[i].y); // ���������� ��������

                }

                // �������� �����
                for (int i = 0; i < N; i++)
                {
                    mass[i].x += mass[i].vx * delay;
                    mass[i].y += mass[i].vy * delay ;

                }

                // �������� �������

                object.movement();


                //  �������������� ������� � ��������
                for (int i = 0; i < v.size(); i++)
                {

                    object.Bar_interaction(check,v[i]);


                }




                // ���� � ������

                for (int i = 0; i < keys.size(); i++)
                {

                    int check1 = check;
                    check = object.Key_interaction(keys[i],check);
                    if (check1 <  check )
                    {
                        keys.erase(keys.begin()+i);
                        v.clear();
                    }

                }

                // �������� �� ����� �� �������
                if (object.x < 0 or object.x > L or object.y < 0 or object.y > H) object.health = 0;

                timer = 0;

            }

        }

        window.clear(Color:: White);





        if (check == 1)
        {
            object.g_down = 0;
            object.g_left = G_left;
        }

        if (check == 2)
        {
            object.g_down = -G_down;
            object.g_left = 0;

        }

       for (int i = 0; i < v.size(); i++) // �������
        {
            RectangleShape rectangle(Vector2f(v[i].dx, v[i].dy));
            rectangle.move(v[i].x,v[i].y );
            rectangle.setFillColor(Color(230, 230, 230));
            window.draw(rectangle);
        }

        for (int i = 0; i < keys.size(); i++ ) // �����
        {


            CircleShape circle5(40);
            circle5.setFillColor(Color(0, 0, 230));
            circle5.move(keys[i].x + (tr_r - 40)/sqrt(2) , keys[i].y  + (tr_r - 40)/sqrt(2));
            window.draw(circle5);

            CircleShape triangle(tr_r, 3);
            triangle.setFillColor(Color(230, 230, 0));
            triangle.move(keys[i].x, keys[i].y);
            //cout << keys[i].x;
            window.draw(triangle);


        }



            for (int i = 0; i < N; i++ ) // ����� �����
        {
            CircleShape circle(r);
            circle.setFillColor(Color(0, 230, 230));
            circle.move(mass[i].x, mass[i].y);
            window.draw(circle);


        }

        // ����� ������
        CircleShape circle1(object.r, 4);
        circle1.setFillColor(Color(230, 0, 230));
        circle1.move(object.x, object.y);
        window.draw(circle1);


        // ����� �� ����� �������� ���������


        Text text;
        text.setFont(font);
        text.setCharacterSize(20);
        text.setFillColor(sf::Color::Blue);

        stringstream objectHealth;
        objectHealth << object.health;
        text.setString(" ��������:" + objectHealth.str());
        text.setPosition (L/2, 0);
        window.draw(text);
        }

        if (object.health <= 0)
        {


            Event event1;
        while (window.pollEvent(event1))
		{
			// ������������ ����� �� �������� � ����� ������� ����?
			if (event1.type == Event::Closed)
			{
				// ����� ��������� ���
				window.close();
			}
		}

        Text text2;
        text2.setFont(font);
        text2.setCharacterSize(35);
        text2.setFillColor(sf::Color::Blue);


        text2.setString("�� �������� ! ");
        text2.setPosition (L/4  , H/4);
        window.draw(text2);

        }

        if (check == 3)
        {

            window.clear(Color:: White);
        Text text1;
        text1.setFont(font);
        text1.setCharacterSize(20);
        text1.setFillColor(sf::Color::Blue);


        text1.setString("�� ������� ! ");
        text1.setPosition (L/4  , H/4);
        window.draw(text1);
        Event event;
                    while (window.pollEvent(event))
            {



                if (event.type == Event::Closed) window.close();
                //if (object.health < 0) window.close();
            }

        }



		window.display();

    }



    delete[] mass;
    return 0;
}
