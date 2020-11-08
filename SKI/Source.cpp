#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include<iostream>
#include<sstream>



using namespace sf;
using namespace std;

////////////////////////////////////////////////////����� ������////////////////////////
class ski { // ����� ������
public:
	float x, y, w,dx,dy, h; //���������� ������ � � �, ������ ������, ��������� (�� � � �� �), ���� ��������
	int dir = 0; //����������� (direction) �������� ������
	
	String File; //���� � �����������
	Image image;//���� �����������
	Texture texture;//���� ��������
	Sprite sprite;//���� ������
};

class updator : public ski {
public:
	virtual void move(float time,int dir) //������� "���������" ������� ������. ��������� � ���� ����� SFML , ���������� ���� �������� ����������, ����� ��������� ��������.
	{
		switch (dir)//��������� ��������� � ����������� �� �����������. (������ ����� ������������� �����������)
		{
		case 1: dx = -0.3; dy = 0;   break;
		case 2: dx = 0.3; dy = 0;   break;
		case 3: dx = 0; dy = -0.6; if (y < 0-w) { y += 800; x = rand() % 1280; } break;
		}
		x += dx * time;
		y += dy * time;

		sprite.setPosition(x, y); //������� ������ � ������� x y , ����������. ���������� ������� � ���� �������, ����� �� ��� ������ ����� �� �����.
	}
};

class ski_obj : public updator {
public:
	ski_obj(String F, float X, float Y, float W, float H) {  //����������� � �����������(�����������) . ��� �������� ������� ������ �� ����� �������� ��� �����, ���������� � � �, ������ � ������

		File = F;//��� �����+����������
		w = W; h = H;//������ � ������
		image.loadFromFile("images/" + File);//���������� � image ���� ����������� ������ File �� ��������� ��, ��� �������� ��� �������� �������.
		texture.loadFromImage(image);//���������� ���� ����������� � ��������
		sprite.setTexture(texture);//�������� ������ ���������

		x = X; y = Y;//���������� ��������� �������
		sprite.setTextureRect(IntRect(0, 0, w, h));  
	}
};

int main()
{

	SoundBuffer back_music;
	if (!back_music.loadFromFile("sound/soundtrack.wav"))
		return -1;
	Sound sound;
	sound.setBuffer(back_music);
	sound.play();
	


	Clock clock;
	
	srand(time(0));
	RenderWindow window(sf::VideoMode(1280, 720), "SKI");

	ski_obj snow("snow.png", 0, 0, 1280, 720);
	ski_obj man("man.png", 600, 150, 108, 137);
	ski_obj drop("drop.png", 0, 0, 68, 76);
	ski_obj lose("lose.png", 0, 0, 1280, 720);
	ski_obj first("start.png", 0, 0, 1280, 720);
	ski_obj gorka("gorka.png", rand() % 1280-202, 720, 202, 154);
	ski_obj gorka2("gorka.png", rand() % 1280-202, 650, 202, 154);
	ski_obj gorka3("gorka.png", rand() % 1280-202, 770, 202, 154);
	ski_obj gorka4("gorka.png", rand() % 1280-202, 590, 202, 154);
	ski_obj rock("rock.png", rand() % 1280-75, 750, 75, 56);
	ski_obj tree1("tree1.png", rand() % 1280-64, 800, 64, 84);
	ski_obj tree2("tree2.png", rand() % 1280-46, 900, 46, 64);
	ski_obj tree3("tree3.png", rand() % 1280-71, 950, 71, 153);




	bool play = false;
	bool start = false;
	

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 800;

		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		man.sprite.setScale(1.2, 1.2);
		if (Keyboard::isKeyPressed(Keyboard::Enter)) {

			start = true;
			play = true;
		}
		
		if (!start) {
			window.draw(first.sprite);
		}
		if (start) {
			
			if((Keyboard::isKeyPressed(Keyboard::A)|| Keyboard::isKeyPressed(Keyboard::Left))&&play) {
				man.move(time, 1);
			}
			if ((Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::Right))&&play) {
				man.move(time, 2);
			}
			if (play) {
				gorka.move(time, 3);
				gorka2.move(time, 3);
				gorka3.move(time, 3);
				gorka4.move(time, 3);
				rock.move(time, 3);
				tree1.move(time, 3);
				tree2.move(time, 3);
				tree3.move(time, 3);
			}
			
			
			window.draw(snow.sprite);
			window.draw(gorka.sprite);
			window.draw(gorka2.sprite);
			window.draw(gorka3.sprite);
			window.draw(gorka4.sprite);
			man.sprite.setOrigin(54, 137);
			
			if ((man.x>tree1.x&&man.x<tree1.x+64&& man.y>tree1.y&&man.y<tree1.y+84)||(man.x > tree2.x&& man.x<tree2.x + 46 && man.y>tree2.y&& man.y < tree2.y + 64)|| (man.x > tree3.x&& man.x<tree3.x + 71 && man.y>tree3.y&& man.y < tree3.y + 153)|| (man.x > rock.x&& man.x<rock.x + 75 && man.y>rock.y&& man.y < rock.y + 56)) {
				drop.sprite.setPosition(man.x, man.y);
				window.draw(drop.sprite);
				window.draw(lose.sprite);
				play = false;
				if (Keyboard::isKeyPressed(Keyboard::R)) {
					play = true;
				}
			}
			else
				window.draw(man.sprite);
			window.draw(rock.sprite);
			window.draw(tree1.sprite);
			window.draw(tree2.sprite);
			window.draw(tree3.sprite);

		}
		
		
		window.display();
	}
	return 0;
}