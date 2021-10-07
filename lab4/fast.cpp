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

    //vector<Point> points = points;
    /////////////////////////////////////////////////////////////////////////////
    // Draw any lines that you find in 'points' using the function 'window->draw'.
    unsigned int lenght_of_vector = points.size();
    while (true)
    {   
        if(lenght_of_vector < 4 ) break;
        Point origo = points.back();
        points.pop_back();
        lenght_of_vector--;
        PolarSorter comparator(origo);
        
        sort(points.begin(), points.end(), comparator);
  
        // GAMMAL  
        // sort(points.begin(), points.end(),
        //     [origo](Point &a, Point &b){
        //         return a.slopeTo(origo) > b.slopeTo(origo);
        //     });
        // cout << "Origo is: " << origo << endl;
        // for(auto e: points){
        //     cout << e << "  " << e.slopeTo(origo) << "  ";
        // }
        //cout << endl;

        int draw_line {0};
        for(int i{0}; i < lenght_of_vector - 1; ++i)
        {
            if(points[i].slopeTo(origo) == points[i + 1].slopeTo(origo))
            {
                draw_line++;
                cout << draw_line << endl;
                if(draw_line >= 2 && i == lenght_of_vector - 2)
                {
                    for(int k{0}; k < draw_line + 1 ; k++){
                        cout << "Drawing a line from " << origo << " to " << points[i + 1 - k] << endl;
                        window->draw(origo, points[i + 1 - k]);
                    }
                    
                    draw_line = 0;
                }
                
            }
            else{
                cout << "Draw_line is: " <<  draw_line << endl;
                if(draw_line >= 2)
                {
                    for(int k{0}; k < draw_line + 1 ; k++){
                        cout << "Drawing a line from " << origo << " to " << points[i - k] << endl;
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
