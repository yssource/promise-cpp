/*
 * Promise API implemented by cpp as Javascript promise style 
 *
 * Copyright (c) 2016, xhawk18
 * at gmail.com
 *
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "asio/timer.hpp"
#include <stdio.h>
#include <boost/asio.hpp>

using namespace promise;
using namespace boost::asio;

Defer testTimer(io_service &io) {

    return delay(io, 3000).then([&] {
        printf("timer after 3000 ms!\n");
        return delay(io, 1000);
    }).then([&] {
        printf("timer after 1000 ms!\n");
        return delay(io, 12000);
    }).then([] {
        printf("timer after 12000 ms!\n");
    }).fail([] {
        printf("timer cancelled!\n");
    });
}

int main() {
    io_service io;

    Defer timer = testTimer(io);

    delay(io, 4500).then([=] {
        printf("clearTimeout\n");
        clearTimeout(timer);
    });

    io.run();
    return 0;
}
