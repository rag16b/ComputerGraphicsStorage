// C++ include
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

// Image writing library
#define STB_IMAGE_WRITE_IMPLEMENTATION // Do not include this line twice in your project!
#include "stb_image_write.h"
#include "utils.h"

// Shortcut to avoid Eigen:: and std:: everywhere, DO NOT USE IN .h
using namespace std;
using namespace Eigen;

struct Sphere{Vector3d center, color; double rad;};

double findT(Vector3d ray_origin, Vector3d center, double rad, Vector3d ray_direction)
{
      	const double sphere_radius = rad;
	double innerSqrtPart = ((ray_origin-center).dot(ray_origin-center)-(rad*rad));
	double discriminant = (ray_direction.dot(ray_origin-center)*ray_direction.dot(ray_origin-center))-(ray_direction.dot(ray_direction))*(innerSqrtPart);
	double t0 = ((-1*ray_direction).dot(ray_origin-center)+sqrt(discriminant))/(ray_direction.dot(ray_direction));
	double t1 = ((-1*ray_direction).dot(ray_origin-center)-sqrt(discriminant))/(ray_direction.dot(ray_direction));
	double t;
	t = (t0 < t1) ? t0 : t1;
	return t;
}

void part1_1()
{
    std::cout << "Part 1.1: Simple ray tracer, two spheres with orthographic projection" << std::endl;

    const std::string filename("part1_1.png");

    MatrixXd R = MatrixXd::Zero(800,800); // Store red value
    MatrixXd G = MatrixXd::Zero(800,800); // Store green value
    MatrixXd B = MatrixXd::Zero(800,800); // Store blue value
    MatrixXd A = MatrixXd::Zero(800,800); // Store the alpha mask

    // The camera is orthographic, pointing in the direction -z and covering the unit square (-1,1) in x and y
    Vector3d origin(-1,1,1);
    Vector3d x_displacement(2.0/R.cols(),0,0);
    Vector3d y_displacement(0,-2.0/R.rows(),0);

    // Double light source
    const Vector3d light_position(0,1,1);
    const Vector3d light_position2(0,-1,1);

    for (unsigned i=0;i<R.cols();i++)
    {
        for (unsigned j=0;j<R.rows();j++)
        {
            // Prepare the ray
            Vector3d ray_origin = origin + double(i)*x_displacement + double(j)*y_displacement;
            Vector3d ray_direction = RowVector3d(0,0,-1);

            	// Intersect with the sphere
		Sphere sphere;
		sphere.center = Vector3d(-0.5,0,0);
		sphere.rad = 0.3;
		sphere.color = Vector3d(0,0,0);
		
		double t = findT(ray_origin,sphere.center,sphere.rad,ray_direction);
		Vector3d p = ray_origin + t*(ray_direction);
            if (t>0)
            {
                // The ray hit the sphere, compute the exact intersection point
                Vector3d ray_intersection = p;

		// Compute normal at the intersection point
                Vector3d ray_normal = ray_intersection.normalized();
		
                // Simple diffuse model
		Vector3d l = (light_position-ray_intersection).normalized().transpose();
		Vector3d vPlusl = (ray_origin-ray_intersection).normalized().transpose() + (light_position-ray_intersection).normalized().transpose();
		Vector3d h = vPlusl/vPlusl.norm();
		
		R(i,j) = max(ray_normal.dot(l)+sphere.color(0), 0.);
		G(i,j) = max(ray_normal.dot(l)+sphere.color(1), 0.);
		B(i,j) = max(ray_normal.dot(l)+sphere.color(2), 0.);
		
                // Disable the alpha mask for this pixel
                A(i,j) = 1;
            }
		
		sphere.center = Vector3d (0.5,0,0);
		sphere.color = Vector3d (0,0,0);
		t = findT(ray_origin,sphere.center,sphere.rad,ray_direction);
		p = ray_origin + t*(ray_direction);
            if (t>0)
            {
                // The ray hit the sphere, compute the exact intersection point
                Vector3d ray_intersection = p;

		// Compute normal at the intersection point
                Vector3d ray_normal = ray_intersection.normalized();
		
                // Simple diffuse model
		Vector3d l = (light_position-ray_intersection).normalized().transpose();
		Vector3d vPlusl = (ray_origin-ray_intersection).normalized().transpose() + (light_position-ray_intersection).normalized().transpose();
		Vector3d h = vPlusl/vPlusl.norm();
		
		R(i,j) = max(ray_normal.dot(l)+sphere.color(0), 0.);
		G(i,j) = max(ray_normal.dot(l)+sphere.color(1), 0.);
		B(i,j) = max(ray_normal.dot(l)+sphere.color(2), 0.);

                // Disable the alpha mask for this pixel
                A(i,j) = 1;
            }
        }
    }

    // Save to png
    write_matrix_to_png(R,G,B,A,filename);
}

void part1_2()
{
    std::cout << "Part 1.2: Two spheres of different colors, one with specular shading." << std::endl;

    const std::string filename("part1_2.png");

    MatrixXd R = MatrixXd::Zero(800,800); // Store red value
    MatrixXd G = MatrixXd::Zero(800,800); // Store green value
    MatrixXd B = MatrixXd::Zero(800,800); // Store blue value
    MatrixXd A = MatrixXd::Zero(800,800); // Store the alpha mask
	
    // The camera is orthographic, pointing in the direction -z and covering the unit square (-1,1) in x and y
    Vector3d origin(-1,1,1);
    Vector3d x_displacement(2.0/R.cols(),0,0);
    Vector3d y_displacement(0,-2.0/R.rows(),0);

    // Double light source
    const Vector3d light_position(0,1,1);
    const Vector3d light_position2(0,-1,1);

    for (unsigned i=0;i<R.cols();i++)
    {
        for (unsigned j=0;j<R.rows();j++)
        {
            // Prepare the ray
            Vector3d ray_origin = origin + double(i)*x_displacement + double(j)*y_displacement;
            Vector3d ray_direction = RowVector3d(0,0,-1);

            	// Intersect with the sphere
		Sphere sphere;
		sphere.center = Vector3d(-0.5,0,0);
		sphere.rad = 0.3;
		sphere.color = Vector3d(0,0.3,0.7);
		
		double t = findT(ray_origin,sphere.center,sphere.rad,ray_direction);
		Vector3d p = ray_origin + t*(ray_direction);
            if (t>0)
            {
                // The ray hit the sphere, compute the exact intersection point
                Vector3d ray_intersection = p;

		// Compute normal at the intersection point
                Vector3d ray_normal = ray_intersection.normalized();
		
                // Simple diffuse model
		Vector3d l = (light_position-ray_intersection).normalized().transpose();
		Vector3d vPlusl = (ray_origin-ray_intersection).normalized().transpose() + (light_position-ray_intersection).normalized().transpose();
		Vector3d h = vPlusl/vPlusl.norm();
		
		R(i,j) = max(ray_normal.dot(l)+sphere.color(0), 0.);
		G(i,j) = max(ray_normal.dot(l)+sphere.color(1), 0.);
		B(i,j) = max(ray_normal.dot(l)+sphere.color(2), 0.);
		
		// Second light source calculations
        	Vector3d l2 = (light_position2-ray_intersection).normalized().transpose();
		Vector3d vPlusl2 = (ray_origin-ray_intersection).normalized().transpose() + (light_position2-ray_intersection).normalized().transpose();
		Vector3d h2 = vPlusl2/vPlusl2.norm();
		// Add second light source
        	R(i,j) += max(ray_normal.dot(l2)+sphere.color(0),0.);
        	G(i,j) += max(ray_normal.dot(l2)+sphere.color(1),0.);
        	B(i,j) += max(ray_normal.dot(l2)+sphere.color(2),0.);

                // Disable the alpha mask for this pixel
                A(i,j) = 1;
            }
		
		sphere.center = Vector3d (0.5,0,0);
		sphere.color = Vector3d (0.5,0,0.5);
		t = findT(ray_origin,sphere.center,sphere.rad,ray_direction);
		p = ray_origin + t*(ray_direction);
            if (t>0)
            {
                // The ray hit the sphere, compute the exact intersection point
                Vector3d ray_intersection = p;

		// Compute normal at the intersection point
                Vector3d ray_normal = ray_intersection.normalized();
		
                // Simple diffuse model
		Vector3d l = (light_position-ray_intersection).normalized().transpose();
		Vector3d vPlusl = (ray_origin-ray_intersection).normalized().transpose() + (light_position-ray_intersection).normalized().transpose();
		Vector3d h = vPlusl/vPlusl.norm();
		
		R(i,j) = max(ray_normal.dot(l)+sphere.color(0), 0.);
		G(i,j) = max(ray_normal.dot(l)+sphere.color(1), 0.);
		B(i,j) = max(ray_normal.dot(l)+sphere.color(2), 0.);

		// Second light source calculations
        	Vector3d l2 = (light_position2-ray_intersection).normalized().transpose();
		Vector3d vPlusl2 = (ray_origin-ray_intersection).normalized().transpose() + (light_position2-ray_intersection).normalized().transpose();
		Vector3d h2 = vPlusl2/vPlusl2.norm();
		// Add second light source
        	R(i,j) += max(ray_normal.dot(l2)+sphere.color(0),0.);
        	G(i,j) += max(ray_normal.dot(l2)+sphere.color(1),0.);
        	B(i,j) += max(ray_normal.dot(l2)+sphere.color(2),0.);

                // Add Specular
		int phong = 1;		// constant had to be small because of distance of light from sphere
               	R(i,j) += pow(max(ray_normal.dot(h), 0.),phong);
               	G(i,j) += pow(max(ray_normal.dot(h), 0.),phong);
               	B(i,j) += pow(max(ray_normal.dot(h), 0.),phong);

                // Disable the alpha mask for this pixel
                A(i,j) = 1;
            }
        }
    }

    // Save to png
    write_matrix_to_png(R,G,B,A,filename);
}

void part1_3()
{
    std::cout << "Part 1.3: Implementing perspective projection." << std::endl;

    const std::string filename("part1_3.png");

    MatrixXd R = MatrixXd::Zero(800,800); // Store red value
    MatrixXd G = MatrixXd::Zero(800,800); // Store green value
    MatrixXd B = MatrixXd::Zero(800,800); // Store blue value
    MatrixXd A = MatrixXd::Zero(800,800); // Store the alpha mask

    // The camera is orthographic, pointing in the direction -z and covering the unit square (-1,1) in x and y
    Vector3d origin(-1,1,1);
    Vector3d x_displacement(2.0/R.cols(),0,0);
    Vector3d y_displacement(0,-2.0/R.rows(),0);

    // Double light source
    const Vector3d light_position(0,1,1);
    const Vector3d light_position2(0,-1,1);

    for (unsigned i=0;i<R.cols();i++)
    {
        for (unsigned j=0;j<R.rows();j++)
        {
            // Prepare the ray
            Vector3d ray_origin = origin + double(i)*x_displacement + double(j)*y_displacement;
            Vector3d ray_direction = RowVector3d(0,0,-1);

		// changing values for perspective view
		origin = Vector3d(-0.5,0.5,1);
		Vector3d w(0,0,1);
		Vector3d p2 = ray_origin;
		ray_origin = origin;
		ray_direction = p2 - w*2;

            	// Intersect with the sphere
		Sphere sphere;
		sphere.center = Vector3d(-0.32,0,0);
		sphere.rad = 0.3;
		sphere.color = Vector3d(0,0.3,0.7);
		
		double t = findT(ray_origin,sphere.center,sphere.rad,ray_direction);
		Vector3d p = ray_origin + t*(ray_direction);
            if (t>0)
            {
                // The ray hit the sphere, compute the exact intersection point
                Vector3d ray_intersection = p;

		// Compute normal at the intersection point
                Vector3d ray_normal = ray_intersection.normalized();
		
                // Simple diffuse model
		Vector3d l = (light_position-ray_intersection).normalized().transpose();
		Vector3d vPlusl = (ray_origin-ray_intersection).normalized().transpose() + (light_position-ray_intersection).normalized().transpose();
		Vector3d h = vPlusl/vPlusl.norm();
		
		R(i,j) = max(ray_normal.dot(l)+sphere.color(0), 0.);
		G(i,j) = max(ray_normal.dot(l)+sphere.color(1), 0.);
		B(i,j) = max(ray_normal.dot(l)+sphere.color(2), 0.);

                // Add Specular
		int phong = 16;
               	R(i,j) += pow(max(ray_normal.dot(h), 0.),phong);
               	G(i,j) += pow(max(ray_normal.dot(h), 0.),phong);
               	B(i,j) += pow(max(ray_normal.dot(h), 0.),phong);

                // Disable the alpha mask for this pixel
                A(i,j) = 1;
            }
		
		sphere.center = Vector3d (0.25,0,0);
		sphere.color = Vector3d (0.5,0,0.5);
		t = findT(ray_origin,sphere.center,sphere.rad,ray_direction);
		p = ray_origin + t*(ray_direction);
            if (t>0)
            {
                // The ray hit the sphere, compute the exact intersection point
                Vector3d ray_intersection = p;

		// Compute normal at the intersection point
                Vector3d ray_normal = ray_intersection.normalized();
		
                // Simple diffuse model
		Vector3d l = (light_position-ray_intersection).normalized().transpose();
		Vector3d vPlusl = (ray_origin-ray_intersection).normalized().transpose() + (light_position-ray_intersection).normalized().transpose();
		Vector3d h = vPlusl/vPlusl.norm();
		
		R(i,j) = max(ray_normal.dot(l)+sphere.color(0), 0.);
		G(i,j) = max(ray_normal.dot(l)+sphere.color(1), 0.);
		B(i,j) = max(ray_normal.dot(l)+sphere.color(2), 0.);

                // Add Specular
		int phong = 16;
               	R(i,j) += pow(max(ray_normal.dot(h), 0.),phong);
               	G(i,j) += pow(max(ray_normal.dot(h), 0.),phong);
               	B(i,j) += pow(max(ray_normal.dot(h), 0.),phong);

                // Disable the alpha mask for this pixel
                A(i,j) = 1;
            }
        }
    }

    // Save to png
    write_matrix_to_png(R,G,B,A,filename);
}

void part1_5()
{
    std::cout << "Part 1.5: Implementation of Shadows" << std::endl;

    const std::string filename("part1_5.png");

    MatrixXd R = MatrixXd::Zero(800,800); // Store red value
    MatrixXd G = MatrixXd::Zero(800,800); // Store green value
    MatrixXd B = MatrixXd::Zero(800,800); // Store blue value
    MatrixXd A = MatrixXd::Zero(800,800); // Store the alpha mask

    // The camera is orthographic, pointing in the direction -z and covering the unit square (-1,1) in x and y
    Vector3d origin(-1,1,1);
    Vector3d x_displacement(2.0/R.cols(),0,0);
    Vector3d y_displacement(0,-2.0/R.rows(),0);

    // Double light source
    const Vector3d light_position(-1.5,1,1);
    const Vector3d light_position2(1,0,1);

    for (unsigned i=0;i<R.cols();i++)
    {
        for (unsigned j=0;j<R.rows();j++)
        {
            // Prepare the ray
            Vector3d ray_origin = origin + double(i)*x_displacement + double(j)*y_displacement;
            Vector3d ray_direction = RowVector3d(0,0,-1);

		// changing values for perspective view
		origin = Vector3d(-0.5,0.5,1);
		Vector3d w(0,0,1);
		Vector3d p2 = ray_origin;
		ray_origin = origin;
		ray_direction = p2 - w*2;

            	// Intersect with the sphere
		Sphere sphere;
		sphere.center = Vector3d(0,0,-0.5);
		sphere.rad = 0.3;
		sphere.color = Vector3d(0,0.3,0.7);
		
		double t = findT(ray_origin,sphere.center,sphere.rad,ray_direction);
		Vector3d p = ray_origin + t*(ray_direction);
            if (t>0)
            {
                // The ray hit the sphere, compute the exact intersection point
                Vector3d ray_intersection = p;

		// Compute normal at the intersection point
                Vector3d ray_normal = ray_intersection.normalized();
		
                // Simple diffuse model
		Vector3d l = (light_position-ray_intersection).normalized().transpose();
		Vector3d vPlusl = (ray_origin-ray_intersection).normalized().transpose() + (light_position-ray_intersection).normalized().transpose();
		Vector3d h = vPlusl/vPlusl.norm();
		
		R(i,j) = max(ray_normal.dot(l)+sphere.color(0), 0.);
		G(i,j) = max(ray_normal.dot(l)+sphere.color(1), 0.);
		B(i,j) = max(ray_normal.dot(l)+sphere.color(2), 0.);

                // Disable the alpha mask for this pixel
                A(i,j) = 1;
            }
		
		sphere.center = Vector3d(-0.8,0,0);
		sphere.rad = 0.5;
		sphere.color = Vector3d (0.5,0,0.5);
		t = findT(ray_origin,sphere.center,sphere.rad,ray_direction);
		p = ray_origin + t*(ray_direction);
            if (t>0)
            {
                // The ray hit the sphere, compute the exact intersection point
                Vector3d ray_intersection = p;

		// Compute normal at the intersection point
                Vector3d ray_normal = ray_intersection.normalized();
		
                // Simple diffuse model
		Vector3d l = (light_position-ray_intersection).normalized().transpose();
		Vector3d vPlusl = (ray_origin-ray_intersection).normalized().transpose() + (light_position-ray_intersection).normalized().transpose();
		Vector3d h = vPlusl/vPlusl.norm();
		
		if (R(i,j) != 0, G(i,j) != 0, B(i,j) != 0){	// trying to make sure both spheres are drawn properly
			R(i,j) = max(ray_normal.dot(l)+sphere.color(0), 0.);
			G(i,j) = max(ray_normal.dot(l)+sphere.color(1), 0.);
			B(i,j) = max(ray_normal.dot(l)+sphere.color(2), 0.);
		}
                // Disable the alpha mask for this pixel
                A(i,j) = 1;
            }
        }
    }

    // Save to png
    write_matrix_to_png(R,G,B,A,filename);
}

void part1_6()
{
    std::cout << "Part 1.6: A reflection of spheres." << std::endl;

    const std::string filename("part1_6.png");

    MatrixXd R = MatrixXd::Zero(800,800); // Store red value
    MatrixXd G = MatrixXd::Zero(800,800); // Store green value
    MatrixXd B = MatrixXd::Zero(800,800); // Store blue value
    MatrixXd A = MatrixXd::Zero(800,800); // Store the alpha mask
	
    // The camera is orthographic, pointing in the direction -z and covering the unit square (-1,1) in x and y
    Vector3d origin(-1,1,1);
    Vector3d x_displacement(2.0/R.cols(),0,0);
    Vector3d y_displacement(0,-2.0/R.rows(),0);

    // Double light source
    const Vector3d light_position(0,0,1);

    for (unsigned i=0;i<R.cols();i++)
    {
        for (unsigned j=0;j<R.rows();j++)
        {
            // Prepare the ray
            Vector3d ray_origin = origin + double(i)*x_displacement + double(j)*y_displacement;
            Vector3d ray_direction = RowVector3d(0,0,-1);

            	// Intersect with the sphere
		Sphere sphere;
		sphere.center = Vector3d(0,0.5,0);
		sphere.rad = 0.3;
		sphere.color = Vector3d(0.5,0,0);
		
		double t = findT(ray_origin,sphere.center,sphere.rad,ray_direction);
		Vector3d p = ray_origin + t*(ray_direction);
            if (t>0)
            {
                // The ray hit the sphere, compute the exact intersection point
                Vector3d ray_intersection = p;

		// Compute normal at the intersection point
                Vector3d ray_normal = ray_intersection.normalized();
		
                // Simple diffuse model
		Vector3d l = (light_position-ray_intersection).normalized().transpose();
		Vector3d vPlusl = (ray_origin-ray_intersection).normalized().transpose() + (light_position-ray_intersection).normalized().transpose();
		Vector3d h = vPlusl/vPlusl.norm();
		
		R(i,j) = max(ray_normal.dot(l)+sphere.color(0), 0.);
		G(i,j) = max(ray_normal.dot(l)+sphere.color(1), 0.);
		B(i,j) = max(ray_normal.dot(l)+sphere.color(2), 0.);
		
                // Add Specular
		int phong = 32;		// constant had to be small because of distance of light from sphere
               	R(i,j) += pow(max(ray_normal.dot(h), 0.),phong);
               	G(i,j) += pow(max(ray_normal.dot(h), 0.),phong);
               	B(i,j) += pow(max(ray_normal.dot(h), 0.),phong);

                // Disable the alpha mask for this pixel
                A(i,j) = 1;
            }
		
		sphere.center = Vector3d (0,-0.7,0);
		sphere.rad = 0.7;
		sphere.color = Vector3d (0.25,0.25,0.25);
		t = findT(ray_origin,sphere.center,sphere.rad,ray_direction);
		p = ray_origin + t*(ray_direction);
            if (t>0)
            {
                // The ray hit the sphere, compute the exact intersection point
                Vector3d ray_intersection = p;

		// Compute normal at the intersection point
                Vector3d ray_normal = ray_intersection.normalized();
		
                // Simple diffuse model
		Vector3d l = (light_position-ray_intersection).normalized().transpose();
		Vector3d vPlusl = (ray_origin-ray_intersection).normalized().transpose() + (light_position-ray_intersection).normalized().transpose();
		Vector3d h = vPlusl/vPlusl.norm();
		
		// Adding reflections
		Vector3d r = ray_direction - 2*(ray_direction.dot(ray_normal))*ray_normal;
		
		R(i,j) = max(ray_normal.dot(l)+sphere.color(0), 0.);
		G(i,j) = max(ray_normal.dot(l)+sphere.color(1), 0.);
		B(i,j) = max(ray_normal.dot(l)+sphere.color(2), 0.);

                // Add Specular
		int phong = 32;		// constant had to be small because of distance of light from sphere
               	R(i,j) += pow(max(ray_normal.dot(h), 0.),phong) + max(r.dot(h),0.);   // my poorly done reflection
               	G(i,j) += pow(max(ray_normal.dot(h), 0.),phong);// + max(r.dot(),0.);
               	B(i,j) += pow(max(ray_normal.dot(h), 0.),phong);// + max(r.dot(),0.);

                // Disable the alpha mask for this pixel
                A(i,j) = 1;
            }
        }
    }

    // Save to png
    write_matrix_to_png(R,G,B,A,filename);
}

int main()
{
	part1_1();
	part1_2();
	part1_3();
	part1_5();
	part1_6();
	
    return 0;
}
