import math

class Product:
    def __init__(self, name, price):
        self.name = name
        self.price = price

    def get_price(self):
        return self.price

    def get_name(self):
        return self.name


class Item:
    def __init__(self, prod, quantity):
        self.product = prod
        self.quantity = quantity

    def get_item_value(self):
        return self.product.get_price()

    def get_total_value(self):
        return self.product.get_price() * self.quantity

    def get_quantity(self):
        return self.quantity

    def get_item_name(self):
        return self.product.get_name()


class Cart:
    def __init__(self):
        self.sub_total = 0
        self.total_units = 0
        self.gift_wrap_fee = 0
        self.discount_name = "Offers not Valid"
        self.discount_value = 0
        self.total_value = 0
        self.shipping_fee = 0
        self.items = []

    def add_item(self, prod, quantity, gift_wrap):
        if gift_wrap:
            self.gift_wrap_fee += 1
        item = Item(prod, quantity)
        self.items.append(item)
        self.sub_total += item.get_total_value()
        self.total_units += item.get_quantity()

    def flat_10_discount(self):
        if self.sub_total > 200:
            return self.sub_total - 10
        return self.sub_total

    def bulk_5_discount(self):
        total = 0
        for item in self.items:
            if item.get_quantity() > 10:
                total += item.get_total_value() - 0.05 * item.get_total_value()
            else:
                total += item.get_total_value()
        return total

    def bulk_10_discount(self):
        if self.total_units > 20:
            return self.sub_total - 0.1 * self.sub_total
        return self.sub_total

    def tiered_50_discount(self):
        total = self.sub_total
        if self.total_units > 30:
            for item in self.items:
                if item.get_quantity() > 15:
                    total = total - (item.get_quantity() - 15) * (item.get_item_value() * 0.5)
        return total

    def calculate_cart_value(self):
        total = self.sub_total

        flat_10_discount_value = self.flat_10_discount()
        if flat_10_discount_value < total:
            total = flat_10_discount_value
            self.discount_name = "flat_10_discount"
            self.discount_value = self.sub_total - total

        bulk_5_discount_value = self.bulk_5_discount()
        if bulk_5_discount_value < total:
            total = bulk_5_discount_value
            self.discount_name = "bulk_5_discount"
            self.discount_value = self.sub_total - total

        bulk_10_discount_value = self.bulk_10_discount()
        if bulk_10_discount_value < total:
            total = bulk_10_discount_value
            self.discount_name = "bulk_10_discount"
            self.discount_value = self.sub_total - total

        tiered_50_discount_value = self.tiered_50_discount()
        if tiered_50_discount_value < total:
            total = tiered_50_discount_value
            self.discount_name = "tiered_50_discount"
            self.discount_value = self.sub_total - total

        self.shipping_fee = math.ceil(float(self.total_units) / 10) * 5
        self.total_value = total + self.gift_wrap_fee + self.shipping_fee

    def generate_output(self):
        print("Cart Details:")
        for item in self.items:
            print("Product Name:", item.get_item_name())
            print("Quantity:", item.get_quantity())
            print("Total Product Value:", item.get_total_value(), "$\n")

        print("Subtotal:", self.sub_total, "$")
        print("Discount Name:", self.discount_name)
        print("Discount Amount:", self.discount_value, "$")
        print("Shipping Fee:", self.shipping_fee, "$")
        print("Gift Wrap Fee:", self.gift_wrap_fee, "$")
        print("Total:", self.total_value, "$")


class System:
    def __init__(self, products):
        self.cart = Cart()
        self.products = products

    def add_product(self, prod, quantity, gift_wrap):
        self.cart.add_item(prod, quantity, gift_wrap)

    def run(self):
        for product in self.products:
            quantity = int(input(f"Enter quantity required for {product.get_name()}: "))
            gift_wrap = bool(int(input("Gift Wrap (Enter 1 if needed else 0): ")))
            self.add_product(product, quantity, gift_wrap)

        print()
        self.cart.calculate_cart_value()
        self.cart.generate_output()


if __name__ == "__main__":
    productA = Product("productA", 20)
    productB = Product("productB", 40)
    productC = Product("productC", 50)

    system = System([productA, productB, productC])
    system.run()
