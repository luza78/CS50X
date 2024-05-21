#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int h = height;
    int w = width;
    int grey = 0;
    int j = 0;

    for (int i = 0; i < h; i++)
    {
        while (j < width)
        {
            grey = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = grey;
            image[i][j].rgbtGreen = grey;
            image[i][j].rgbtRed = grey;

            j++;
        }
        j = 0;
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int h = height;
    int w = width;
    float sepiaBlue = 0;
    float sepiaGreen = 0;
    float sepiaRed = 0;
    int j = 0;

    for (int i = 0; i < h; i++)
    {
        while (j < width)
        {

            sepiaRed = round((.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue));
            sepiaGreen = round((.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue));
            sepiaBlue = round((.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue));

            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }

            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }

            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            if (sepiaRed < 0)
            {
                sepiaRed = 0;
            }

            if (sepiaGreen < 0)
            {
                sepiaGreen = 0;
            }

            if (sepiaBlue < 0)
            {
                sepiaBlue = 0;
            }

            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtRed = sepiaRed;

            j++;
        }
        j = 0;
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp[height][width];
    int j = 0;

    for (int i = 0; i < height; i++)
    {
        while (j != width)
        {
            tmp[i][j] = image[i][j];
            j++;
        }

        j = 0;
    }

    for (int i = 0; i < height; i++)
    {
        while (j != width)
        {
            image[i][j] = tmp[i][width - j - 1];
            j++;
        }

        j = 0;
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    RGBTRIPLE blur[height][width];

    int j = 0;

    for (int i = 0; i < height; i++)
    {
        // Makes copy of image
        while (j != width)
        {
            copy[i][j] = image[i][j];
            j++;
        }

        j = 0;
    }

    j = 1;

    for (int i = 1; i < height - 1; i++)
    {
        // Blurring middle of image
        while (j < width - 1)
        {
            blur[i][j].rgbtBlue = round((copy[i - 1][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i + 1][j - 1].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i + 1][j + 1].rgbtBlue) / 9.0);
            blur[i][j].rgbtGreen = round((copy[i - 1][j - 1].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i + 1][j - 1].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen) / 9.0);
            blur[i][j].rgbtRed = round((copy[i - 1][j - 1].rgbtRed + copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed + copy[i][j - 1].rgbtRed + copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed + copy[i + 1][j - 1].rgbtRed + copy[i + 1][j].rgbtRed + copy[i + 1][j + 1].rgbtRed) / 9.0);

            image[i][j] = blur[i][j];
            j++;
        }

        j = 1;
    }

    for (int i = 0; i < 1; i++)
    {
        // Blurring top line (not corners)
        while (j < width - 1)
        {
            blur[i][j].rgbtBlue = round((copy[i][j - 1].rgbtBlue + copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i + 1][j - 1].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i + 1][j + 1].rgbtBlue) / 6.0);
            blur[i][j].rgbtGreen = round((copy[i][j - 1].rgbtGreen + copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i + 1][j - 1].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen) / 6.0);
            blur[i][j].rgbtRed = round((copy[i][j - 1].rgbtRed + copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed + copy[i + 1][j - 1].rgbtRed + copy[i + 1][j].rgbtRed + copy[i + 1][j + 1].rgbtRed) / 6.0);

            image[i][j] = blur[i][j];
            j++;
        }

        j = 1;
    }

    for (int i = height - 1; i < height; i++)
    {
        // Blurring bottom line (not corners)
        while (j < width - 1)
        {
            blur[i][j].rgbtBlue = round((copy[i][j - 1].rgbtBlue + copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i - 1][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue) / 6.0);
            blur[i][j].rgbtGreen = round((copy[i][j - 1].rgbtGreen + copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i - 1][j - 1].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen) / 6.0);
            blur[i][j].rgbtRed = round((copy[i][j - 1].rgbtRed + copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed + copy[i - 1][j - 1].rgbtRed + copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed) / 6.0);

            image[i][j] = blur[i][j];
            j++;
        }

        j = 1;
    }

    j = 0;

    for (int i = 1; i < height - 1; i++)
    {
        // Blurring left line (not corners)
        blur[i][j].rgbtBlue = round((copy[i + 1][j].rgbtBlue + copy[i + 1][j + 1].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i - 1][j + 1].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i][j].rgbtBlue) / 6.0);
        blur[i][j].rgbtGreen = round((copy[i + 1][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i - 1][j + 1].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i][j].rgbtGreen) / 6.0);
        blur[i][j].rgbtRed = round((copy[i + 1][j].rgbtRed + copy[i + 1][j + 1].rgbtRed + copy[i][j + 1].rgbtRed + copy[i - 1][j + 1].rgbtRed + copy[i - 1][j].rgbtRed + copy[i][j].rgbtRed) / 6.0);

        image[i][j] = blur[i][j];
    }

    j = width - 1;

    for (int i = 1; i < height - 1; i++)
    {
        // Blurring right line (not corners)
        j = width - 1;
        while (j < width)
        {
            blur[i][j].rgbtBlue = round((copy[i + 1][j].rgbtBlue + copy[i + 1][j - 1].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i - 1][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i][j].rgbtBlue) / 6.0);
            blur[i][j].rgbtGreen = round((copy[i + 1][j].rgbtGreen + copy[i + 1][j - 1].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i - 1][j - 1].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i][j].rgbtGreen) / 6.0);
            blur[i][j].rgbtRed = round((copy[i + 1][j].rgbtRed + copy[i + 1][j - 1].rgbtRed + copy[i][j - 1].rgbtRed + copy[i - 1][j - 1].rgbtRed + copy[i - 1][j].rgbtRed + copy[i][j].rgbtRed) / 6.0);

            image[i][j] = blur[i][j];
            j++;
        }
    }

    j = 0;

    for (int i = 0; i < 1; i++)
    {
        // Blurring top left corner
        while (j < 1)
        {
            blur[i][j].rgbtBlue = round((copy[i + 1][j].rgbtBlue + copy[i + 1][j + 1].rgbtBlue + copy[i][j + 1].rgbtBlue +
                                         copy[i][j].rgbtBlue) /
                                        4.0);
            blur[i][j].rgbtGreen = round((copy[i + 1][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen + copy[i][j + 1].rgbtGreen +
                                          copy[i][j].rgbtGreen) /
                                         4.0);
            blur[i][j].rgbtRed = round((copy[i + 1][j].rgbtRed + copy[i + 1][j + 1].rgbtRed + copy[i][j + 1].rgbtRed + copy[i][j].rgbtRed) /
                                       4.0);

            image[i][j] = blur[i][j];
            j++;
        }
    }

    j = width - 1;

    for (int i = 0; i < 1; i++)
    {
        // Blurring top right corner
        while (j < width)
        {
            blur[i][j].rgbtBlue = round((copy[i + 1][j].rgbtBlue + copy[i + 1][j - 1].rgbtBlue + copy[i][j - 1].rgbtBlue +
                                         copy[i][j].rgbtBlue) /
                                        4.0);
            blur[i][j].rgbtGreen = round((copy[i + 1][j].rgbtGreen + copy[i + 1][j - 1].rgbtGreen + copy[i][j - 1].rgbtGreen +
                                          copy[i][j].rgbtGreen) /
                                         4.0);
            blur[i][j].rgbtRed = round((copy[i + 1][j].rgbtRed + copy[i + 1][j - 1].rgbtRed + copy[i][j - 1].rgbtRed + copy[i][j].rgbtRed) /
                                       4.0);

            image[i][j] = blur[i][j];
            j++;
        }
    }

    j = 0;

    for (int i = height - 1; i < height; i++)
    {
        // Blurring bottom left corner
        while (j < 1)
        {
            blur[i][j].rgbtBlue = round((copy[i - 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue + copy[i][j + 1].rgbtBlue +
                                         copy[i][j].rgbtBlue) /
                                        4.0);
            blur[i][j].rgbtGreen = round((copy[i - 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen + copy[i][j + 1].rgbtGreen +
                                          copy[i][j].rgbtGreen) /
                                         4.0);
            blur[i][j].rgbtRed = round((copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed + copy[i][j + 1].rgbtRed + copy[i][j].rgbtRed) /
                                       4.0);

            image[i][j] = blur[i][j];
            j++;
        }
    }

    j = width - 1;

    for (int i = height - 1; i < height; i++)
    {
        // Blurring bottom right corner
        while (j < width)
        {
            blur[i][j].rgbtBlue = round((copy[i - 1][j].rgbtBlue + copy[i - 1][j - 1].rgbtBlue + copy[i][j - 1].rgbtBlue +
                                         copy[i][j].rgbtBlue) /
                                        4.0);
            blur[i][j].rgbtGreen = round((copy[i - 1][j].rgbtGreen + copy[i - 1][j - 1].rgbtGreen + copy[i][j - 1].rgbtGreen +
                                          copy[i][j].rgbtGreen) /
                                         4.0);
            blur[i][j].rgbtRed = round((copy[i - 1][j].rgbtRed + copy[i - 1][j - 1].rgbtRed + copy[i][j - 1].rgbtRed + copy[i][j].rgbtRed) /
                                       4.0);

            image[i][j] = blur[i][j];
            j++;
        }
    }

    return;
}
