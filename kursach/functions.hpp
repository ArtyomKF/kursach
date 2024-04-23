void
mirrorFunc (Rgb** arr, char axis, int left, int up, int right, int down, int H, int W);

void
copyFunc(Rgb** arr, int left, int up, int right, int down, int newLeft, int newUp, int H, int W);

void
replaceFunc(Rgb** arr, int r, int g, int b, int newR, int newG, int newB, int W, int H);

void
filterFunc(Rgb** arr, std::string component, int compVal, int H, int W);

void
printHelp ();