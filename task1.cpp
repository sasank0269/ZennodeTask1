#include<bits/stdc++.h>
using namespace std;

class Product{

    string name;
    int price;

    public:

    Product(string name, int price ){
        this->price = price;
        this->name = name;
    }

    int getPrice(){
        return price;
    }

    string getName(){
        return name;
    }

};

class Item{

    
    Product *product;
    int quantity;
    int totalValue;

    public:
    Item(Product *prod, int quantity){
        product = prod;
        this->quantity = quantity;
    }

    int getItemValue(){
        return product->getPrice();
    }

    int getTotalValue(){
        return product->getPrice()*quantity;
    }

    int getQuantity(){
        return quantity;
    }

    string getItemName(){
        return product->getName();
    }

};

class Cart{

    int subTotal;
    int totalUnits;
    int giftWrapFee;
    string discountName;
    int discountValue;
    int totalValue;
    int shippingFee;


    int flat_10_discount(){

        if(subTotal>200){
            return subTotal-10;
        }
        return subTotal;
    }

    int bulk_5_discount(){
        int total = 0;

        for(int i=0; i<items.size(); i++){
            if(items[i]->getQuantity()>10){
                total += items[i]->getTotalValue() - 0.05*items[i]->getTotalValue();
            }
            else total+=items[i]->getTotalValue();
        }

        return total;
    }

    int bulk_10_discount(){

        if(totalUnits>20) return subTotal-0.1*subTotal;
        return subTotal;
    }

    int tiered_50_discount(){
        
        int total = subTotal;
        if(totalUnits>30){
            for(int i=0; i<items.size(); i++){
                if(items[i]->getQuantity()>15){
                    total = total - (items[i]->getQuantity() - 15)*(items[i]->getItemValue()*0.5);
                }
            }
        }
        return total;
    }

    public:
    vector<Item*> items;

    Cart(){
        subTotal = 0;
        totalUnits = 0;
        giftWrapFee = 0;
        discountValue = 0;
        discountName = "Offers not Valid";
        totalValue = 0;
        shippingFee = 0;
    }

    void addItem(Product *prod, int quantity, bool giftWrap){
        if(giftWrap) giftWrapFee++;
        Item *it1 = new Item(prod, quantity);
        items.push_back(it1);
        subTotal+=it1->getTotalValue();
        totalUnits+=it1->getQuantity();
    }

    

    void caluclateCartValue(){

        int total = subTotal;

        int flat_10_discount_value = flat_10_discount();

        if(flat_10_discount_value<total){
            total = flat_10_discount_value;
            discountName = "flat_10_discount";
            discountValue = subTotal-total;
        }

        int bulk_5_discount_value = bulk_5_discount();

        if(bulk_5_discount_value<total){
            total = bulk_5_discount_value;
            discountName = "bulk_5_discount";
            discountValue = subTotal-total;
        }

        int bulk_10_discount_value = bulk_10_discount();

        if(bulk_10_discount_value<total){
            total = bulk_10_discount_value;
            discountName = "bulk_10_discount";
            discountValue = subTotal-total;
        }

        int tiered_50_discount_value = tiered_50_discount();

        if(tiered_50_discount_value<total){
            total = tiered_50_discount_value;
            discountName = "tiered_50_discount";
            discountValue = subTotal-total;
        }

        shippingFee = ceil(float(totalUnits)/10)*5;

        totalValue = total + giftWrapFee + shippingFee;

    }

    void generateOutput(){

        cout<<"Cart Details: "<<endl;
        for(int i=0; i<items.size(); i++){
            cout<<"Product Name: "<<items[i]->getItemName()<<endl;
            cout<<"Quantity: "<<items[i]->getQuantity()<<endl;
            cout<<"Total Product Value: "<<items[i]->getTotalValue()<<"$"<<endl;
            cout<<endl;
        }

        cout<<"Subtotal: "<<subTotal<<"$"<<endl;
        cout<<"Discount Name: "<<discountName<<endl;
        cout<<"Discount Amount: "<<discountValue<<"$"<<endl;

        cout<<"Shipping Fee: "<<shippingFee<<"$"<<endl;
        cout<<"Gift Wrap Fee: "<<giftWrapFee<<"$"<<endl;
        cout<<"Total: "<<totalValue<<"$"<<endl;
    }


};

class System{

    public:
    Cart *cart;
    vector<Product*> products;

    System(vector<Product*> products){
        cart = new Cart();
        this->products = products;
    }

    void addProduct(Product *prod, int quantity, bool giftWrap){
        cart->addItem(prod, quantity, giftWrap);
    }

    void run(){

        for(int i=0; i<products.size(); i++){
            int quantity;
            bool giftWrap;
            cout<<"Enter quantity required for "<<products[i]->getName()<<": "<<endl;
            cin>>quantity;

            cout<<"Gift Wrap( Enter 1 if needed else 0): "<<endl;
            cin>>giftWrap;

            addProduct(products[i], quantity, giftWrap);
        }
        cout<<endl;
        cart->caluclateCartValue();
        cart->generateOutput();
    }



};

int main(){

    Product *productA = new Product("productA", 20);
    Product *productB = new Product("productB", 40);
    Product *productC = new Product("productC", 50);

    System system({productA, productB, productC});
    system.run();

    return 0;
}