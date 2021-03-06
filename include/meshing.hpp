#ifndef MESHING_HPP
#define MESHING_HPP

#include "hull.hpp"
#include "util.hpp"
#include <CL/cl.hpp>
#include <Eigen/Dense>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include <omp.h>
#include <sys/time.h>
#include <time.h>
#include <vector>

static std::vector<Point> DEFAULT_VECTOR;
class Meshing {

private:
  sf::RenderWindow *window;
  std::vector<Point> points;

public:
  Meshing(int witdh, int height, sf::RenderWindow *win = NULL);

  //  *** triangulation ***
  int triangulation(int nb_partition);
  int triangulation_rec(int nb_partition);
  std::vector<Point> partition(std::vector<Point> list_points,
                               std::vector<Point> &H1, std::vector<Point> &H2,
                               bool vertical,
                               std::vector<Point> old_path = DEFAULT_VECTOR);
  std::vector<Point>
  partition_path(std::vector<Point> list_points, bool vertical,
                 std::vector<Point> old_path = DEFAULT_VECTOR);
  void partitionRec(std::vector<Point> points_set, std::vector<Point> Edges,
                    bool vertival, int deph_rec,
                    std::vector<Partition> &partitions);
  void ParDeTri(std::vector<Point> points_set, std::vector<Edge> edge_list,
                std::vector<Triangle> &triangle_list);
  int nearest_point_cpu(std::vector<Point> ps, Edge &e);
  int nearest_point_gpu(std::vector<Point> &ps, Edge &e);
  int nearest_point(std::vector<Point> &ps, Edge &e);
  int convex_hull(Eigen::MatrixXd points);
  int side(Point p, std::vector<Point> &path, bool vertical);
  bool is_goodtriangle(std::vector<Point> &LIST, Point &ps, Edge &e);

  // *** Graphic ***
  void draw_point(int x, int y, sf::Color = sf::Color::White);
  void draw_points();
  void draw_points(std::vector<Point> points,
                   sf::Color color = sf::Color::White);
  void draw_line(float x1, float y1, float x2, float y2,
                 sf::Color color = sf::Color::White);
  void draw_triangle(Triangle t, sf::Color color = sf::Color::White);
};

bool not_in_vect(std::vector<Point> vect_point, Point p);
float dd(Edge e, Point p);
float dd2(Edge e, Point p);
std::vector<Edge> point_vect_to_vect_edge(std::vector<Point> &ps);
void update(Edge e, std::vector<Edge> &L);
int points_to_matrix(std::vector<Point> vect_points);

#endif
