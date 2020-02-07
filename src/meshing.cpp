#include "meshing.hpp"
#include "hull.cpp"

using namespace std;
using namespace Eigen;


Meshing::Meshing(int witdh, int height, sf::RenderWindow  *win ){
    window = win;
    window->setFramerateLimit(1);
    MatrixXd points_eigen = MatrixXd::Random(100,2)*witdh;
    points_eigen = points_eigen.array().abs();

    for(int i = 0; i < points_eigen.rows(); i++){
        points.push_back(Point(points_eigen(i,0), points_eigen(i,1), i));
    }
}


int Meshing::triangulation(){
    // copy vector
    vector<Point> proj;
    // find median
    std::vector<float> xcoord;
    for (int i=0; i<points.size(); i++){
        xcoord.push_back(points[i].x);
     }
    int n = sizeof(xcoord)/sizeof(xcoord[0]); 
    sort(xcoord.begin(),  xcoord.end());
    float median  = xcoord[xcoord.size()/2];
    
    //3d projection
    vector<Point> hull;
    for(int i = 0; i < points.size(); i++){
        proj.push_back(Point(points[i].y,pow(points[i].x-median, 2) + pow(points[i].y,2), points[i].index));
    }
    // delauney path :
    hull = quickHull(proj);
    for (int i = 0; i < hull.size(); i++ ){
        int index = hull[i].index;
        draw_point( points[index].x, points[index].y, sf::Color::Red);
    }
}


void Meshing::draw_point(int x, int y, sf::Color color){
    sf::RectangleShape s{sf::Vector2f(4, 4)};
    s.setPosition(static_cast<float>(x), static_cast<float>(y));
    s.setFillColor(color);
    window->draw(s);
}
void Meshing::draw_points(vector<Point> p, sf::Color color){
    for(int i = 0; i < p.size(); i++){
        draw_point(p[i].x, p[i].y, color);
    }
}

void Meshing::draw_points(){
    for(int i = 0; i < points.size(); i++){
        draw_point(points[i].x, points[i].y);
    }
}

void Meshing::draw_line(int x1, int y1, int x2, int y2){
    sf::Vertex line[2];
    line[0].position = sf::Vector2f(x1, y1);
    line[0].color  = sf::Color::Red;
    line[1].position = sf::Vector2f(x2, y2);
    line[1].color = sf::Color::Red;
    window->draw(line, 2, sf::Lines);

}


int points_to_matrix(vector<Point> vect_points){
    for( int i = 0; i < vect_points.size(); i++){
        std:cout << i << std::endl;
    }
    return 1;
}



int main(int argc, char **argv){


    sf::RenderWindow window(sf::VideoMode(800, 600), "Delaunay triangulation");
    Meshing mesh = Meshing(800, 800, &window);
    mesh.draw_points();

    mesh.triangulation();

	window.display();

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
	}

	return 0;
}
 