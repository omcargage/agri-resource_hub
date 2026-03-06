#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib> 
#include <ctime>
#include <regex>   // For regex validation of phone number

using namespace std;

// Function to generate a mock OTP
int generateOTP() {
    srand(time(0)); // For seeding the random number generator
    int otp = rand() % 9000 + 1000; // Generating a 4-digit OTP
    return otp;
}

// Function to validate phone number using regex (exactly 10 digits)
bool isValidPhoneNumber(const string& phone)
{
    regex phoneRegex("^[0-9]{10}$"); // Regex pattern for exactly 10 digits
    return regex_match(phone, phoneRegex);
}

// Function for registering a new farmer
void registerFarmer() 
{
    string username, password, phone, name;
    int phonenumberattempts = 3; // For Allowing 3 attempts to enter a valid phone number
    cout << "Enter your first name: ";
    cin>>name;
    cout << "Enter a new username: ";
    cin >> username;
    cout << "Enter a new password: ";
    cin >> password;

    // Loop for phone number validation with 3 attempts
    while (phonenumberattempts > 0) 
    {
        cout << "Enter your 10-digit phone number (without country code): ";
        cin >> phone;

        if (isValidPhoneNumber(phone)) {
            // If phone number is valid, proceeds.
            break;
        } else {
            // If phone number is invalid, reduce attempts and displays error
            phonenumberattempts--;
            if (phonenumberattempts > 0) {
                cout << "Invalid phone number. Please try again (" << phonenumberattempts << " attempts left)." << endl;
            } else {
                cout << "Registration failed: Invalid phone number entered 3 times." << endl;
                return; // Exits registration if 3 attempts fail
            }
        }
    }

    // Generates and displays the OTP on the terminal(mock sending it via SMS)
    int generatedOTP = generateOTP();
    cout << "\nMock OTP sent to " << phone << ": " << generatedOTP << endl;

    // Ask the farmer to enter the OTP they received
    int enteredOTP;
    int OTPattempts = 3;
    while (OTPattempts > 0) 
    {
    cout << "Enter the OTP you received: ";
    cin >> enteredOTP;

   // Verify the OTP 
    
        if (enteredOTP == generatedOTP) 
        {
            // OTP verified, proceeding with registration
            cout << "OTP verified successfully!" << endl;

            // Saving credentials in a file
            ofstream outfile("farmers.txt", ios::app); // Open file in append mode
            if (outfile.is_open()) {
                outfile << name << " " << username << " " << password << " " << phone << endl;
                cout << "||\t\t Registration successful! \t\t||" << endl;
            } else {
                cout << "Error: Unable to open file for registration." << endl;
            }
            outfile.close();
            break;
        } 
        else
        {
            // OTP mismatch
            OTPattempts--;
            if (OTPattempts > 0) 
            {
                cout << "Invalid OTP. Please try again (" << OTPattempts << " attempts left)."<<endl;
            }
            else
            {
                cout << "Invalid OTP. Registration failed." << endl;
                return; // Exits registration if 3 attempts fail
            }
        }
    }
}

// Function for logging in
bool loginFarmer(string &loggedInUser) {
    string username, password, storedUsername, storedPassword, storedphone, farmername;
    cout << "Enter username or your Registered contact number: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    // Reading credentials from the file
    ifstream infile("farmers.txt");
    if (infile.is_open()) {
        while (infile >> farmername >> storedUsername >> storedPassword >> storedphone) {
            if (((storedUsername == username) || (storedphone == username)) && (storedPassword == password)) {
                loggedInUser = farmername; // Storing the logged-in username
                cout << "||\\_/\\|\t\t              Login successful!              \t\t|\\_/\\||" << endl;
                infile.close();
                return true;
            }
        }
        cout << "||\t\t Login failed: Invalid username or password.\t\t||" << endl;
        infile.close();
    } else {
        cout << "Error: Unable to open file for login." << endl;
    }
    return false;
}

// Function to display recent agricultural updates
void displayRecentUpdates() {
    vector<string> updates = {
        "1. New water conservation techniques introduced for dry regions.",
        "2. Government announces subsidies for organic farming.",
        "3. New pest control methods developed for wheat crops."
    };
    
    cout << "\nRecent Updates in Agriculture:\n";
    for (const string &update : updates) {
        cout << "- " << update << endl;
    }
}

// Function to display current crop prices
void displayCropPrices() {
    cout << "\nCurrent Crop Prices (per quintal):\n";
    cout << "Wheat: Rs. 2,400\n";
    cout << "Rice: Rs. 2,600\n";
    cout << "Sugarcane: Rs. 3,000\n";
}

// Function to display weather forecast
void displayWeatherPrediction() {
    cout << "\nWeather Forecast for the next 3 days:\n";
    cout << "Day 1: Sunny, 25 Degrees Celcius\n";
    cout << "Day 2: Cloudy, 22 Degrees Celcius\n";
    cout << "Day 3: Light Rain, 20 Degrees Celcius\n";
}

// Function to display the app menu
void displayMenu() {
    cout << "\nApp Menu:\n";
    cout << "1. Book Consulting Session\n";
    cout << "2. Book Soil Testing Slot\n";
    cout << "3. Rent Machinery\n";
    cout << "4. View Upcoming Training Sessions\n";
    cout << "5. Ask a Question\n";
    cout << "6. Go back to Dashboard\n";
    cout << "7. Leave feedback and suggestions.\n";
    cout << "8. Exit the app.\n";
}

// Function to book a consultation session
void bookConsultationSession(const string &loggedinuser) {
    string date, time, mailid;
    
    cout << "\nBooking Consultation Session\n";
    cout << "Enter desired date for consultation (e.g., 15/12/2024): ";
    cin >> date;
    cout << "Enter desired time for consultation (e.g., 14:30): ";
    cin >> time;
    cout<<"Enter your E-mail ID, for our convenience : ";
    cin>>mailid;

    // Saving the booking details in a file
    ofstream outfile("consultation_bookings.txt", ios::app); // Append mode
    if (outfile.is_open()) {
        outfile << loggedinuser << "," << date << "," << time << "," << mailid << endl; // Save farmer's name, email id, and booking details
        cout << "\n||/\\/\\|[]|\t\t Consultation session booked successfully for " << date << " at " << time << "!\t\t|[]|/\\/\\||\n";
    } else {
        cout << "Error: Unable to save the booking.\n";
    }
    outfile.close();
}

// Function to book a soil testing slot
void bookSoilTestingSlot(const string &loggedinuser) {
    string date, time, mailid2;
    
    cout << "\nBooking Soil Testing Slot\n";
    cout << "Enter desired date for soil testing (e.g., 20/12/2024): ";
    cin >> date;
    cout << "Enter desired time for soil testing (e.g., 10:00): ";
    cin >> time;
    cout<<"Enter your E-mail ID, for our convenience : ";
    cin>>mailid2;

    // Saving the soil testing slot booking details in a file
    ofstream outfile("soil_testing_slots.txt", ios::app); // Append mode
    if (outfile.is_open()) {
        outfile << loggedinuser << "," << date << "," << time << "," << mailid2 << endl; // Save farmer's name, date, and time, and mail id
        cout << "\n||/\\/\\|[]|\t\tSoil testing slot booked successfully for " << date << " at " << time << "!\t\t|[]|/\\/\\||\n";
        cout<<"\n||/\\/\\|[]|\t\t Our team will reach out to you, soon! Thank you! \t\t|[]|/\\/\\||\n"<<endl;
    } else {
        cout << "Error: Unable to save the booking.\n";
    }
    outfile.close();
}

// Function to book machinery rental
void bookMachineryRental(const string &loggedinuser) {
    string machinery, email, startDate;
    int attempts = 3;
    int choice, rentalDays;
    double dailyRate, totalCost;
    const double cautionDeposit = 1000.0; // Fixed caution deposit

    cout << "\n ||/\\/\\|\t\tMachinery Rental Service\t\t|/\\/\\||\n" << endl;
    cout << "Available Machinery:\n";
    cout << "\n1. Tractor (Rs.2500/day)\n";
    cout << "2. Cultivator (Rs.1500/day)\n";
    cout << "3. Seed Drill (Rs. 1200/day)\n";
    cout << "4. Seed Counter (Rs. 1000/day)\n";
    cout << "5. Sprayer (Rs. 800/day)\n";
    cout << "6. Harvesting Equipment (Rs. 3000/day)\n";
    cout << "7. Loader (Rs. 2000/day)\n";
    
     // Validating input
    while (attempts>0) {
        cout << "\nEnter your choice (1-7): ";
        cin >> choice;
        if (cin.fail() && attempts!=0) { // If input is invalid
            attempts--;
            cin.clear();  // Clearing error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignoring invalid input
            cout << "Invalid input. (You have " << attempts << " attempts left Now) ";
            
        } else if (((choice < 1) || (choice > 7)) && attempts!=0) { // If number is out of range, and there are attempts left
            attempts--;
            cout << "Invalid choice. (You have " << attempts << " attempts left Now) ";
            
        } else {
            break; // Valid input
        }
    }

    // Determining machinery and daily rate using switch statement
    switch (choice) {
        case 1:
            machinery = "Tractor";
            dailyRate = 2500.0;
            break;
        case 2:
            machinery = "Cultivator";
            dailyRate = 1500.0;
            break;
        case 3:
            machinery = "Seed Drill";
            dailyRate = 1200.0;
            break;
        case 4:
            machinery = "Seed Counter";
            dailyRate = 1000.0;
            break;
        case 5:
            machinery = "Sprayer";
            dailyRate = 800.0;
            break;
        case 6:
            machinery = "Harvesting Equipment";
            dailyRate = 3000.0;
            break;
        case 7:
            machinery = "Loader";
            dailyRate = 2000.0;
            break;
        default:
            cout << "\nReturning to main menu\n";
            return;
    }

    // Collecting additional details
    cout << "Enter your email ID: ";
    cin >> email;
    cout << "Enter the rental duration in days: ";
    cin >> rentalDays;
    cout << "Enter the rental start date (e.g., 2024-12-05): ";
    cin >> startDate;

    // Calculating total cost
    totalCost = (dailyRate * rentalDays) + cautionDeposit;

    // Save booking details to file
    ofstream outfile("machinery_rentals.txt", ios::app); // Append mode
    if (outfile.is_open()) {
        outfile << loggedinuser << "," << machinery << "," << rentalDays << " days,"
                << startDate << "," << email << ",Rs." << totalCost << endl;
        cout << "\nMachinery rented successfully!\n";
        cout << "Machinery: " << machinery << "\n";
        cout << "Rental Duration: " << rentalDays << " days\n";
        cout << "Start Date: " << startDate << "\n";
        cout << "Caution Deposit: Rs." << cautionDeposit << "\n";
        cout << "Total Cost: Rs." << totalCost << "\n";
    } else {
        cout << "Error: Unable to save the booking.\n";
    }
    outfile.close();
}

// Function to view upcoming training sessions
void viewTrainingSessions(const string &loggedinuser) {
    // List of training sessions
    vector<string> sessions = {
        "1. Sustainable Farming Practices (2024-12-10, 10:00 AM)",
        "2. Organic Fertilizer Preparation (2024-12-15, 2:00 PM)",
        "3. Efficient Irrigation Techniques (2024-12-20, 11:00 AM)",
        "4. Pest Management Strategies (2024-12-25, 9:00 AM)",
        "5. Modern Farming Tools Workshop (2025-01-05, 1:00 PM)"
    };

    cout << "\n--- Upcoming Training Sessions ---" << endl;
    for (const auto &session : sessions) {
        cout << session << endl;
    }

    // Asking if the farmer is interested in any session
    int choice;
    cout << "\nEnter the number of the session you're interested in (or 0 to skip): ";
    cin >> choice;

    if (choice == 0) {
        cout << "You chose not to register for any session.\n";
        return;
    } else if (choice > 0 && choice <= static_cast<int>(sessions.size())) {
        // Saving the farmer's interest to a file
        ofstream outfile("training_interest.txt", ios::app); // Append mode
        if (outfile.is_open()) {
            outfile << loggedinuser << "," << sessions[choice - 1] << endl; // Save farmer's name and session details
            cout << "You have successfully registered interest in:\n" << sessions[choice - 1] << endl;
        } else {
            cout << "Error: Unable to save your registration.\n";
        }
        outfile.close();
    } else {
        cout << "Invalid choice. Please try again.\n";
    }
}

// Function to allow farmers to ask questions
void askQuestion(const string &loggedinuser) {
    string email, question;

    cout << "\n--- Ask a Question ---" << endl;
    cout << "Enter your email ID: ";
    cin >> email;
    cin.ignore(); // To ignore the newline character left by previous input
    cout << "Enter your question: ";
    getline(cin, question); // Using getline to capture multi-word input

    // Saving the question to a file
    ofstream outfile("questions.txt", ios::app); // Append mode
    if (outfile.is_open()) {
        outfile << "Farmer Name: " << loggedinuser << "\n";
        outfile << "Email ID: " << email << "\n";
        outfile << "Question: " << question << "\n";
        outfile << "------------------------------------\n";
        cout << "\nYour question has been submitted successfully. Thank you!\n";
        cout << "Our Team will reach back to you with the solutions, in the span of next 2 working days. ";
    } else {
        cout << "Error: Unable to save your question. Please try again.\n";
    }
    outfile.close();
}

// Function to allow farmers to leave multi-line feedback and suggestions
void leaveFeedback(const string &loggedinuser) {
    string feedback, line;
    
    cout << "\nLeave your feedback and suggestions for Agri-Resource Hub below:" << endl;
    cout << "(Type 'END' on a new line when you are done)\n";
    
    // Taking input of multiple lines of feedback
    while (true) {
        getline(cin, line);
        if (line == "END") break; // Stopping to take input when 'END' is entered
        feedback += line + "\n";  // Appending each line to feedback
    }

    // Saving the feedback to a file
    ofstream feedbackFile("feedback_suggestions.txt", ios::app); // Append mode
    if (feedbackFile.is_open()) {
        feedbackFile << "Farmer: " << loggedinuser << "\nFeedback: " << feedback << "---------------------\n";
        cout << "Thank you for your valuable feedback, "<<loggedinuser<< endl;
    } else {
        cout << "Error: Unable to save your feedback. Please try again later.\n";
    }
    feedbackFile.close();
}


// Function to handle the dashboard with menu toggle option
void dashboard(const string &loggedinuser) {
    cout << "\n ||_/_/ \t\t Welcome to Agri-Resource Hub, " << loggedinuser << "! \t\t \\_\\_||"  << "\n";
    cout << "\nWhat would you like to do?\n";

    displayRecentUpdates();
    displayCropPrices();
    displayWeatherPrediction();

    char choice;
    cout << "\nWould you like to open the app menu? (y/n): ";
    cin >> choice;

    if (choice == 'y' || choice == 'Y') {
        int menuChoice;
        do {
            displayMenu();
            cout << "\nEnter your choice: ";
            cin >> menuChoice;
            switch (menuChoice) {
                case 1:
                    bookConsultationSession(loggedinuser);
                    break;
                case 2:
                    bookSoilTestingSlot(loggedinuser);
                    break;
                case 3:
                    bookMachineryRental(loggedinuser);
                    break;
                case 4:
                    viewTrainingSessions(loggedinuser);
                    break;
                case 5:
                    askQuestion(loggedinuser);
                    break;
                case 6:
                    dashboard(loggedinuser);  // Displaying the dashboard again
                    break;
                case 7:
                    leaveFeedback(loggedinuser);
                    break;
                case 8:
                    cout << "||/\\_\t\tExiting the app. Thank you so much, "<< loggedinuser <<"!\t\t_/\\||\n";
                    break;
                default:
                    cout << "Invalid choice. Please try again.\n";
            }
        } while (menuChoice != 8);
    } else {
        cout << "||_/_/ \t\t Thank you for using Agri-Resource hub!\t\t \\_\\_||\n";
        cout << "||_/_/ \t\t          Have a great day!       \t\t \\_\\_||" << endl;
    }
}


int main() {
    string loggedinuser;
    int choice;
    cout << "||_/_/ \t\t Welcome to the Agri-Resource Hub!\t\t \\_\\_||" << endl;
    cout << "1. Register\n2. Login\nEnter choice: ";
    cin >> choice;

    if (choice == 1) {
        registerFarmer();
    } else if (choice == 2) {
        if (loginFarmer(loggedinuser)) 
        {
            dashboard(loggedinuser);  // Displays the dashboard after a successful login
        } 
        else 
        {
            cout << "||\t\t               Please try again.\t\t        ||" << endl;
        }
    } else 
    {
        cout << "/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\" << endl;
        cout << "||\t\t   INVALID CHOICE ![kindly choose between the numbers 1 and 2.]\t\t        ||" << endl;
        cout << "\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/" << endl;
    }


    return 0;
}
//BACKUP LABEL - 29TH NOVEMBER - 2024.
//BACKUP LABEL - 2ND DECEMBER - 2024.
//BACKUP LABEL - 3RD DECEMBER - 2024.
//BACKUP LABEL - 4TH DECEMBER - 2024.


