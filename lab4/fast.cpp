/*
 * fast < input.txt
 *
 * Compute and plot all line segments involving 4 points in input.txt
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <chrono>
#include "point.h"
#include "window.h"

using namespace std;

int main(int argc, const char* argv[]) {
    WindowPtr window = create_window(argc, argv);

    // The array of points
    vector<Point> points;

    // Read points from cin
    int N{};
    cin >> N;

    for (int i{0}; i < N; ++i) {
        unsigned int x, y;
        cin >> x >> y;
        points.push_back(Point{x, y});
    }

    // draw points to screen all at once
    window->draw(points);

    // sort points by natural order
    // makes finding endpoints of line segments easy
    sort(points.begin(), points.end());

    auto begin = chrono::high_resolution_clock::now();

    /////////////////////////////////////////////////////////////////////////////
    // Draw any lines that you find in 'points' using the function 'window->draw'.
    unsigned int length_of_vector = points.size();
    while (true) // N - 2 gånger
    {   
        if(length_of_vector < 4 ) break;
        Point origo = points.back();
        points.pop_back();
        length_of_vector--;
        PolarSorter comparator(origo);
        
        sort(points.begin(), points.end(), comparator); //N * logN gånger

        // cout << "Origo is: " << origo << endl;
        // for(auto e: points){
        //     cout << e << "  " << e.slopeTo(origo) << "  ";
        // }
        //cout << endl;

        int draw_line {0};
        for(int i{0}; i < length_of_vector - 1; ++i) // N gånger
        {
            if(points[i].slopeTo(origo) == points[i + 1].slopeTo(origo))
            {
                draw_line++;
                if(draw_line >= 2 && i == length_of_vector - 2)
                {
                    for(int k{0}; k < draw_line + 1 ; k++){
                        window->draw(origo, points[i + 1 - k]);
                    }
                    
                    draw_line = 0;
                }
                
            }
            else{
                if(draw_line >= 2)
                {
                    for(int k{0}; k < draw_line + 1 ; k++){
                        window->draw(origo, points[i - k]);
                    }
                }
                draw_line = 0;
            }
            
        }
    }
    for(auto origo: points)
    {
        sort(points.begin(), points.end(),
        [origo](Point &a, Point &b){
            return origo.slopeTo(a) > origo.slopeTo(a);
        });
    }


    /////////////////////////////////////////////////////////////////////////////

    auto end = chrono::high_resolution_clock::now();
    cout << "Computing line segments took "
         << std::chrono::duration_cast<chrono::milliseconds>(end - begin).count()
         << " milliseconds." << endl;

    // wait for user to terminate program
    window->run();

    return 0;
}
