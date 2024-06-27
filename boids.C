void setStyle(){
  gROOT->SetStyle("Plain");
  gStyle->SetPalette(57);
  gStyle->SetOptTitle(0);
}

void grafico(){

    // Instance of the graph
    TGraphErrors * graph =new TGraphErrors(n_points,x_vals,y_vals,0,y_errs); 

    graph->SetTitle("Posizioni");

    // Cosmetics
    graph->SetMarkerStyle(kOpenCircle);
    graph->SetMarkerColor(kBlue);
    graph->SetLineColor(kBlue);

    // The canvas on which we'll draw the graph
    TCanvas *myCanvas = new TCanvas();

    gStyle->SetOptFit(111);
    graph->Draw("APE");
 
    leg->Draw("Same");

    myCanvas->Print("Posizioni.gif");
}