/**
 * @file ft_ankeralarm.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2023-06-06
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "../factory_test.h"



void FactoryTest::_showAnkeralarmScreen()
{
    printf("enter Ankeralarm Screen\n");

    _canvas->setFont(&fonts::Font0);

    long old_position = _enc_pos;
    int selected_option = 0;
    const int num_options = 3; // Schwoikreis, Kettenlänge, Exit
    int schwoikreis = 50;
    int kettenlaenge = 40;
    char string_buffer[20];
    bool editing = false;

    _enc_pos = 0;
    _enc.setPosition(_enc_pos);

    while (1)
    {
        _canvas->fillScreen((uint32_t)0x87C38F);

        _canvas->fillRect(0, 0, 240, 25, (uint32_t)0x07430F);
        _canvas->setTextSize(2);
        _canvas->setTextColor((uint32_t)0x87C38F);
        snprintf(string_buffer, 20, "Ankeralarm");
        _canvas->drawCenterString(string_buffer, _canvas->width() / 2, 5);

        _canvas->setTextSize(2);
        _canvas->setTextColor((uint32_t)0x07430F);

        // Highlight the selected option
        for (int i = 0; i < num_options; i++)
        {
            if (i == selected_option)
            {
                if (editing)
                {
                    _canvas->setTextColor((uint32_t)0xFF0000); // Red color for editing
                }
                else
                {
                    _canvas->setTextColor((uint32_t)0xFFFFFF); // White color for selection
                }
            }
            else
            {
                _canvas->setTextColor((uint32_t)0x07430F); // Default color
            }

            switch (i)
            {
            case 0:
                _canvas->setCursor(10, 30);
                snprintf(string_buffer, 20, "Schwoikreis: %dm", schwoikreis);
                _canvas->print(string_buffer);
                break;
            case 1:
                _canvas->setCursor(10, 60);
                snprintf(string_buffer, 20, "Kettenlänge: %dm", kettenlaenge);
                _canvas->print(string_buffer);
                break;
            case 2:
                _canvas->setCursor(10, 90);
                _canvas->print("Exit");
                break;
            }
        }

        _canvas_update();

        if (_check_encoder())
        {
            if (editing)
            {
                if (selected_option == 0)
                {
                    schwoikreis += (_enc_pos > old_position) ? 1 : -1;
                }
                else if (selected_option == 1)
                {
                    kettenlaenge += (_enc_pos > old_position) ? 1 : -1;
                }
            }
            else
            {
                selected_option = (_enc_pos > old_position) ? (selected_option + 1) % num_options : (selected_option - 1 + num_options) % num_options;
            }
            old_position = _enc_pos;
        }

        if (_check_next())
        {
            if (editing)
            {
                editing = false; // Exit editing mode
            }
            else
            {
                if (selected_option == 2)
                {
                    break; // Exit selected
                }
                else
                {
                    editing = true; // Enter editing mode
                }
            }
        }
    }

    printf("quit Ankeralarm screen\n");
}
