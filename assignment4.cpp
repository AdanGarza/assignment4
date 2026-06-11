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

// ===== SECTION: CORE LOGIC =====
    // Determine discount tier and calculate base subtotal
    int discountTier = 0;
    double discountPercent = 0.0;

    if (numRooms >= MIN_ROOMS_TIER3) {
        discountTier = 3;
        discountPercent = DISCOUNT_TIER3;
    } else if (numRooms >= MIN_ROOMS_TIER2) {
        discountTier = 2;
        discountPercent = DISCOUNT_TIER2;
    } else if (numRooms >= MIN_ROOMS_TIER1) {
        discountTier = 1;
        discountPercent = DISCOUNT_TIER1;
    }

    // Calculate subtotal after room discount
    double subtotal = nightlyRate * numRooms * numNights * (1.0 - discountPercent);

    // Apply loyalty discount if 3+ nights
    // Compound condition: both numNights >= 3 AND subtotal > 0 must be true
    // to safely apply the discount (logical AND demonstrates compound condition)
    if (numNights >= MIN_NIGHTS_LOYALTY && subtotal > 0.0) {
        subtotal = subtotal * (1.0 - LOYALTY_DISCOUNT);
    }

    // Calculate tax and total
    double taxAmount = subtotal * (taxRate / 100.0);
    double totalBilling = subtotal + taxAmount;

    // ===== SECTION: SWITCH STATEMENT =====
    switch (discountTier) {
        case 0:
            cout << "No group discount applied (fewer than " << MIN_ROOMS_TIER1 << " rooms)." << '\n';
            break;
        case 1:
            cout << "Group discount: " << (DISCOUNT_TIER1 * 100) << "% applied (" 
                 << MIN_ROOMS_TIER1 << "-" << (MIN_ROOMS_TIER2 - 1) << " rooms)." << '\n';
            break;
        case 2:
            cout << "Group discount: " << (DISCOUNT_TIER2 * 100) << "% applied (" 
                 << MIN_ROOMS_TIER2 << "-" << (MIN_ROOMS_TIER3 - 1) << " rooms)." << '\n';
            break;
        case 3:
            cout << "Group discount: " << (DISCOUNT_TIER3 * 100) << "% applied (" 
                 << MIN_ROOMS_TIER3 << "+ rooms)." << '\n';
            break;
        default:
            cout << "Discount tier calculation error." << '\n';
            break;
    }
    
    // ===== SECTION: RELATIONAL & LOGICAL OPERATOR SHOWCASE =====
    // These conditions demonstrate each relational and logical operator.
    
    // Relational operators: <, >, <=, >=
    if (numRooms < MIN_ROOMS_TIER1) cout << "Booking is below tier 1 threshold (<)." << '\n';  // <
    if (numRooms > MIN_ROOMS_TIER3) cout << "Booking qualifies for highest tier (>)." << '\n';  // >
    if (numNights <= MIN_NIGHTS_LOYALTY) cout << "Stay is short-term (<=)." << '\n';  // <=
    if (nightlyRate >= 100.0) cout << "Premium room rate (>=)." << '\n';  // >=

    // Relational operators: ==, !=
    if (numRooms == numNights) cout << "Room count equals night count (==)." << '\n';  // ==
    if (numRooms != numNights) cout << "Room count differs from night count (!=)." << '\n';  // !=

    // Logical operators: &&, ||, !
    if (numRooms >= MIN_ROOMS_TIER1 && numNights >= MIN_NIGHTS_LOYALTY) {
        cout << "Qualifies for both group and loyalty discounts (&&)." << '\n';  // &&
    }
    if (discountTier == 0 || discountTier == 1) {
        cout << "Qualifies for no or basic group discount (||)." << '\n';  // ||
    }
    if (!(numRooms < MIN_ROOMS_TIER1)) {
        cout << "Meets minimum room threshold (!)." << '\n';  // !
    }

    // ===== SECTION: FLOATING-POINT BUG GUARD =====
    /*
    Floating-Point Equality Warning

    - Why == is unreliable: Floating-point arithmetic can accumulate rounding errors.
      For example, (subtotal * rate / 100.0) may not equal a manually calculated amount.
    - Technique used: avoid direct == comparisons on calculated monetary values;
      instead, I restructured the tax calculation to apply the percentage directly
      without intermediate rounding steps.
    - Chosen approach: calculate tax as subtotal * (taxRate / 100.0) and total as
      subtotal + tax, keeping precision intact. The "/" operator is applied once
      to the tax rate percentage, not to accumulated amounts.
    */

    // ===== SECTION: FORMATTED OUTPUT / RECEIPT =====
    cout << std::fixed << std::setprecision(2);

    cout << "\n----- BILLING RECEIPT -----\n";
    cout << std::left << std::setw(28) << "Nightly rate:" << std::right << "$" << std::setw(10) << nightlyRate << '\n';
    cout << std::left << std::setw(28) << "Rooms:" << std::right << std::setw(11) << numRooms << '\n';
    cout << std::left << std::setw(28) << "Nights:" << std::right << std::setw(11) << numNights << '\n';
    cout << std::left << std::setw(28) << "Group discount:" << std::right << std::setw(9) << (discountPercent * 100) << "%" << '\n';
    cout << std::left << std::setw(28) << "Subtotal:" << std::right << "$" << std::setw(10) << subtotal << '\n';
    cout << std::left << std::setw(28) << "Tax:" << std::right << "$" << std::setw(10) << taxAmount << '\n';
    cout << std::left << std::setw(28) << "Total:" << std::right << "$" << std::setw(10) << totalBilling << '\n';
    // ===== SECTION: KNOWN BUG RISKS =====
    /*
    Known Bug Risks
    1. Floating-point equality in tax calculation: Using == to compare tax amounts
       could fail due to rounding. Prevention: structured calculation to minimize
       intermediate rounding; applied percentage division once to taxRate, not to
       accumulated subtotal values.

    2. Missing break in switch statement: Would cause fall-through printing multiple
       messages. Prevention: included break statements after each case and a default
       clause to catch errors.

    3. Dangling else / inverted logic: The compound condition with && could be written
       incorrectly, applying discount when it shouldn't. Prevention: explicit parentheses
       and clear variable names (numNights >= MIN_NIGHTS_LOYALTY reads unambiguously).
    */

    return 0;
}