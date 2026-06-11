// ============================================================
// Name    : [Adan Garza]
// Course  : COSC 1437 — Programming Fundamentals II
// Date    : [Submission Date]
// Program : Chapter 4 Major Project
// Option  : [A — Hotel Billing]
// Purpose : [Calculates hotel room billing with group discounts
//           and adds loyalty discount for 3+ night stays]
// ============================================================


// ===== SECTION: PSEUDOCODE DESIGN =====).

/* Start

Prompt for nightly rate, number of rooms, number of nights, sales tax rate
  Read all inputs

  Validate inputs
    IF nightly rate <= 0.0
      assert fails (invalid rate)
    IF rooms <= 0 OR nights <= 0
      assert fails (invalid rooms or nights)

  Constants:
    MIN_ROOMS_TIER1 (10), MIN_ROOMS_TIER2 (20), MIN_ROOMS_TIER3 (30)
    DISCOUNT_TIER1 (0.10), DISCOUNT_TIER2 (0.20), DISCOUNT_TIER3 (0.30)
    MIN_NIGHTS_LOYALTY (3), LOYALTY_DISCOUNT (0.05)

  // Determine discount tier
  Compute discountTier = 0 (no discount)
  IF rooms >= 30
    discountTier = 3, discountPercent = 0.30
  ELSE IF rooms >= 20
    discountTier = 2, discountPercent = 0.20
  ELSE IF rooms >= 10
    discountTier = 1, discountPercent = 0.10
  ELSE
    discountTier = 0, discountPercent = 0.0

  // Apply room discount
  Compute subtotal = nightly rate * rooms * nights * (1 - discountPercent)

  // Apply loyalty discount if 3+ nights (compound condition: nights >= 3 AND discountPercent > 0)
  IF nights >= 3
    Apply loyalty discount: subtotal = subtotal * (1 - LOYALTY_DISCOUNT)

  // Compute taxes
  Compute tax = subtotal * (tax rate / 100)
  Compute total = subtotal + tax

  // Switch on discount tier for messaging
  SWITCH discountTier
    CASE 0: print no discount message
    CASE 1: print 10% discount message
    CASE 2: print 20% discount message
    CASE 3: print 30% discount message
    DEFAULT: print error

  // Print formatted receipt

End*/
#include <iostream>
#include <iomanip>
#include <cassert>
#include <string>

// ===== SECTION: CONSTANTS =====
constexpr int MIN_ROOMS_TIER1 = 10;
constexpr int MIN_ROOMS_TIER2 = 20;
constexpr int MIN_ROOMS_TIER3 = 30;
constexpr double DISCOUNT_TIER1 = 0.10;
constexpr double DISCOUNT_TIER2 = 0.20;
constexpr double DISCOUNT_TIER3 = 0.30;
constexpr int MIN_NIGHTS_LOYALTY = 3;
constexpr double LOYALTY_DISCOUNT = 0.05;

int main()
{
    using std::cout;
    using std::cin;
    using std::endl;

    // ===== SECTION: INPUT & VALIDATION =====
    cout << "Hotel Room Billing System" << endl;
    double nightlyRate = 0.0;
    int numRooms = 0;
    int numNights = 0;
    double taxRate = 0.0;

    cout << "Enter nightly rate per room ($): ";
    cin >> nightlyRate;
    
    // Invariant: nightlyRate must be positive
    // If this assert fires, user entered a non-positive room rate
    assert(nightlyRate > 0.0 && "nightlyRate must be positive");

    cout << "Enter number of rooms booked: ";
    cin >> numRooms;

    cout << "Enter number of nights: ";
    cin >> numNights;
    
    // Invariant: numRooms and numNights must both be positive
    // If this assert fires, user entered non-positive values for rooms or nights
    assert((numRooms > 0 && numNights > 0) && "rooms and nights must be positive");

    cout << "Enter sales tax rate (%): ";
    cin >> taxRate;
    
    // ===== SECTION: OPERATOR PRECEDENCE REFERENCE =====
    /*
    Precedence     Operator(s)     Category    Associativity

    1 (highest)    !             Logical NOT      Right-to-left

    2             *, /, %       Multiplicative    Left-to-right

    3            +, -           Additive          Left-to-right

    4           <, <=, >, >=     Relational      Left-to-right

    5              ==, !=        Equality       Left-to-right

    6             &&           Logical AND    Left-to-right

    7 (lowest)    ||          Logical OR     Left-to-right
    */

    // Example evaluation for expression:
    // !(rooms > 0) || (rate >= 50.0 && rooms != nights)
    // Choose sample values: nightlyRate = 75.00, numRooms = 12, numNights = 4
    // Sub-expressions:
    // (rooms > 0)                => (12 > 0)       => true
    // !(rooms > 0)               => !true          => false
    // (rate >= 50.0)             => (75.00 >= 50)  => true
    // (rooms != nights)          => (12 != 4)      => true
    // (rate >= 50.0 && rooms != nights) => (true && true) => true
    // !(rooms > 0) || (rate >= 50.0 && rooms != nights) => (false || true) => true
