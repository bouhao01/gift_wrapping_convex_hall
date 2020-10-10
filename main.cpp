#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const float EPSILON = 1E-9;

typedef struct Point
{
    int x;
    int y;

    bool operator<(const Point &p) const
    {
        if (x < p.x)
            return true;

        else if (x == p.x)
            return (y > p.y) ? true : false;

        else
            return false;
    }

    bool operator==(const Point &p) const
    {
        return (p.x == x) && (p.y == y) ? true:false;
    }
} point;

ostream& operator<<(ostream& stream, const point& p){
    stream << "(" << p.x << ", " << p.y <<")";
    return stream;
}

static point vect(const point &p, const point &q)
{
    Point res = {q.x - p.x, q.y - p.y};
    return res;
}

static float cosine(const point& p, const point &q)
{
    int dot_prod = p.x*q.x + p.y*q.y;
    float norm_2_p = sqrt(pow(p.x , 2) + pow(p.y , 2));
    float norm_2_q = sqrt(pow(q.x , 2) + pow(q.y , 2));
    return dot_prod / (norm_2_p * norm_2_q);
}

void compute_hall(const vector<point>& input_points, vector<point>& output_points)
{

    // get the smallest point (most left-top point)
    point starting_point = input_points.front();
    for(point p : input_points)
    {
        if(p < starting_point)
            starting_point = p;
    }

    output_points.push_back(starting_point);

    // Return one point if the input size is one element.
    if (input_points.size() == 1)
        return;

    point ref_p = {starting_point.x, starting_point.y + 1}
        , ref_q = starting_point
        , next_point = ref_p;

    while (true)
    {
        point next_point = ref_p;

        // Loop over all points and extract the next convex hall point.
        for(point p : input_points)
        {
            if (p == ref_q)
                continue;

            float cos_angle_1 = cosine(vect(ref_p, ref_q), vect(ref_q, p));
            float cos_angle_2 = cosine(vect(ref_p, ref_q), vect(ref_q, next_point));

            // If the three point are collinear, take the smallest
            if(abs(cos_angle_1 - cos_angle_2) < EPSILON)
                next_point = (p < next_point) ? p:next_point;

            else if (cos_angle_1 >  cos_angle_2)
                    next_point = p;
        }

    output_points.push_back(next_point);
    ref_p = ref_q;
    ref_q = next_point;

    // End the algorithm when finding the starting point as the next point of the convex
    if (next_point == starting_point)
        break;

    }
}

int main()
{
    int n;
    vector<point> points, convex_hall;

    cin >> n;

    points.resize(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> points[i].x >> points[i].y;
    }

    compute_hall(points, convex_hall);

    cout << endl << "Convex hall (counter clockwise): " << endl;
    for (point p : convex_hall)
    {
        cout << p << endl;
    }
    return 0;
}