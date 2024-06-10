#include<iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include <string>
#include<memory>

int WHeight = 0;
int WWidth = 0;

class Shape{
    public:
        virtual ~Shape() = default;
        virtual void move(const sf::Vector2f & velocity) = 0;
        virtual sf::FloatRect getBounds() const = 0;
        virtual void handleCollision(const sf::RenderWindow &window, sf::Vector2f& velocity) = 0;
        virtual void setPosition(float x, float y) = 0;
        virtual void setFillColor(const int r, const int g, const int b) = 0;
        virtual void draw(sf::RenderWindow &window) const = 0;
        virtual void setText(std::string & name, sf::Font & font) = 0;
};

class Rectangle : public Shape{
    sf::RectangleShape rectangle;
    sf::Text text;
    public:
        Rectangle(float width, float height): rectangle(sf::Vector2f(width, height)) {}

        sf::FloatRect getBounds() const override{
            return rectangle.getGlobalBounds();
        }
        void move(const sf::Vector2f& velocity) override{
            rectangle.move(velocity);
            text.move(velocity);
        }

        void handleCollision(const sf::RenderWindow &window, sf::Vector2f& velocity) override{
            sf::Vector2f position = rectangle.getPosition();
            sf::FloatRect bounds = rectangle.getGlobalBounds();

            if ( position.x < 0 || position.x + bounds.width > window.getSize().x){
                velocity.x = -velocity.x;
            if (position.x < 0) rectangle.setPosition(0, position.y);
            if (position.x + bounds.width > window.getSize().x) rectangle.setPosition(window.getSize().x - bounds.width, position.y);
           }
            if ( position.y < 0 || position.y + bounds.height > window.getSize().y){
                velocity.y = -velocity.y;
            if (position.y < 0) rectangle.setPosition(position.x, 0);
            if (position.y + bounds.height > window.getSize().y) rectangle.setPosition(position.x, window.getSize().y - bounds.height);
            }
        }
            void setPosition(float x, float y) override{
                rectangle.setPosition(x, y);
            };
            void setFillColor(const int r, const int g, const int b) override{
                rectangle.setFillColor(sf::Color(r, g, b));
            }

            void draw(sf::RenderWindow &window) const override{
                window.draw(rectangle);
                window.draw(text);
            }
            void setText(std::string & name, sf::Font& font) override{
              sf::Vector2f position = rectangle.getPosition();
              sf::FloatRect bounds = rectangle.getGlobalBounds();

              text.setFont(font);
              text.setString(name);
              text.setCharacterSize(14);
              text.setFillColor(sf::Color::White);
              text.setPosition(position.x + bounds.width/2 - text.getLocalBounds().width/2, position.y + bounds.height/2 - text.getLocalBounds().height/2);
            } 

         
};
class Circle : public Shape{
    sf::CircleShape circle;
    sf::Text text;
    public:
        Circle(float radius): circle(radius) {}

        sf::FloatRect getBounds() const override{
            return circle.getGlobalBounds();
        }
        void move(const sf::Vector2f& velocity) override{
            circle.move(velocity);
            text.move(velocity);
        }

        void handleCollision(const sf::RenderWindow &window, sf::Vector2f& velocity){
            sf::Vector2f position = circle.getPosition();
            sf::FloatRect bounds = circle.getGlobalBounds();

            if ( position.x < 0 || position.x + bounds.width > window.getSize().x){
                velocity.x = -velocity.x;
                
                if (position.x < 0) {
                    circle.setPosition(0, position.y);
                }
                
                if (position.x + bounds.width > window.getSize().x) circle.setPosition(window.getSize().x - bounds.width, position.y);
            }
            if ( position.y < 0 || position.y + bounds.height > window.getSize().y){
                velocity.y = -velocity.y;
            if (position.y < 0) circle.setPosition(position.x, 0);
            if (position.y + bounds.height > window.getSize().y) circle.setPosition(position.x, window.getSize().y - bounds.height);
            }
        }
            void setPosition(float x, float y) override{
                circle.setPosition(x, y);
            };
            void setFillColor(const int r,const int g,const int b) override{
                circle.setFillColor(sf::Color(r, g, b));
            }
            void draw(sf::RenderWindow &window)const override{
                window.draw(circle);
                window.draw(text);
            }
            void setText(std::string & name, sf::Font& font) override{
            sf::Vector2f position = circle.getPosition();
            sf::FloatRect bounds = circle.getGlobalBounds();

              text.setFont(font);
              text.setString(name);
              text.setCharacterSize(14);
              text.setFillColor(sf::Color::White);
              text.setPosition(position.x + bounds.width/2- text.getLocalBounds().width/2, position.y + bounds.height/2 - text.getLocalBounds().height/2);
              
            } 
};



int main(){

    std::string rname;
    float rx, ry;
    float sx, sy;
    int r, g, b;
    float size_w, size_h;

    std::string cname;
    float cx, cy;
    float speed_x, speed_y;
    int cr, cg , cb;
    float radius;

    //Open a file 

    std::ifstream File("assignment1.txt");

    //check if file exits or not  
    if ( !File ) {
        std::cout<<"Can't open the file \n";
        return 1;
    }

    //array for storing shapes
    std::vector<std::shared_ptr<Shape>> shapes;

    //array for storing velocity
    std::vector<sf::Vector2f> velocities;

    //array for storing text
    std::vector<sf::Text> texts;

    sf::Font font;
    if ( ! font.loadFromFile("RedditMono-VariableFont_wght.ttf")){
        printf("couldn't load font\n");
        return 1;
    }

    std::string word;


    while ( File >> word ) {
        if ( word == "Window" ) {
            File >> word;
            WWidth = std::stoi(word);
            File >> word;
            WHeight = std::stoi(word);
    }else if ( word == "Rectangle" ) {
              File >> word;
              rname = word;
              File >> word;
              rx = std::stof(word);
              File >> word;
              ry = std::stof(word);
              File >> word;
              sx = std::stof(word);
              File >> word;
              sy = std::stof(word);
              File >> word;
              r = std::stoi(word);
              File >> word;
              g = std::stoi(word);
              File >> word;
              b = std::stoi(word);
              File >> word;
              size_w = std::stof(word);
              File >> word;
              size_h = std::stof(word);

              std::shared_ptr<Shape> rect = std::make_shared<Rectangle>(size_w, size_h);
              rect->setPosition(rx, ry);
              rect->setFillColor(r, g, b);
              rect->setText(rname, font);
              shapes.push_back(rect);

              //storing velocities
              sf::Vector2f velocity(sx, sy);
              velocities.push_back(velocity);

              
              

        }else if( word == "Circle" ) {

              File >> word;
              cname = word;
              File >> word;
              cx = std::stof(word);
              File >> word;
              cy = std::stof(word);
              File >> word;
              speed_x = std::stof(word);
              File >> word;
              speed_y = std::stof(word);
              File >> word;
              cr = std::stoi(word);
              File >> word;
              cg = std::stoi(word);
              File >> word;
              cb = std::stoi(word);
              File >> word;
              radius = stof(word);

              //creating circ pointer
              std::shared_ptr<Shape> circ = std::make_shared<Circle>(radius);
              circ->setPosition(cx, cy);
              circ->setFillColor(cr, cg, cb);
              circ->setText(cname, font);

              shapes.push_back(circ);

              //storing velocities

              sf::Vector2f circ_velocity(speed_x, speed_y);
              velocities.push_back(circ_velocity);


            }
    }
    
    File.close();

    //create a window
    sf::RenderWindow window(sf::VideoMode(WWidth, WHeight), "Shapes");
    window.setFramerateLimit(260);

    while( window.isOpen() ){
        sf::Event event;

        while( window.pollEvent( event ) ){
            if ( event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();

        for ( int i = 0; i < shapes.size(); i++){
            shapes[i]->move(velocities[i]);
            shapes[i]->handleCollision(window, velocities[i]);
            shapes[i]->draw(window);

        }

        window.display();

    }

   return 0; 
}


