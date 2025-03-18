#include "global.h"
#include "Init.h"
#include "SpaceManager.h"
#include "ComponentManager.h"

common::String Email = "lewis.connolly92@gmail.com"; // argv[1]
common::String Password = ""; // argv[2]
common::String SpaceName = "Live D&D Arena"; // argv[3]
common::String ComponentName = "Text Box"; // argv[4]
common::String EntityName = "Big Screen"; // argv[5]
common::String Text = "I HAVE THE POWER!!!!"; // argv[6]

// Make an async call to any function, with any return type 
template <typename ReturnType, typename Func, typename Instance, typename... Args>
ReturnType CallAsyncFunction(Func MemberFunc, Instance* ObjInstance, Args&&... args)
{
    // Create promise and future
    promise<ReturnType> Promise;
    future<ReturnType> Future = Promise.get_future();

    // Start thread - directly call the function with the promise and args
    thread Thread(
        MemberFunc,
        ObjInstance,
        move(Promise),
        forward<Args>(args)...
    );
    
    ReturnType Result = ReturnType(); // Set to default for type

    // Wait for callback with timeout
    future_status Status = Future.wait_for(chrono::seconds(60));
    if (Status == future_status::timeout)
    {
        cout << "Timeout waiting for callback!" << endl;        
    }
    else
    {
        Result = Future.get(); // Get the result        
    }
    
    // Clean up
    Thread.join();

    return Result;
}

int main(int argc, char* argv[]) {
    
    /************* Login *************/
    
    cout << "Initialising connection to tenant..." << endl;
    // Initialise connection to OKO tenant
    Init* Initialise = new Init("https://ogs.magnopus.cloud/", "OKO");

    // Initialise managers
    SpaceManager* SpaceMgr = new SpaceManager();
    ComponentManager* ComponentMgr = new ComponentManager();
    
    
    cout << "Logging in to tenant..." << endl;
    // Log in to tenant with command line email and password arguments
    common::String LoginResult = CallAsyncFunction<common::String>(&Init::LoginToTenant, Initialise, argv[1], argv[2]);    
    
	if (LoginResult != "Success")
	{
		cout << "Login result: " << LoginResult << endl;
		return 0;
	}

    /************* Set Text Component *************/
    
    cout << "Finding space..." << endl;
    // Find D&D space
    //const systems::Space* ConjuringSpace = CallAsyncFunction<const systems::Space*>(&SpaceManager::GetSpaceByName, SpaceMgr, SpaceName);        
    const systems::Space* ConjuringSpace = CallAsyncFunction<const systems::Space*>(&SpaceManager::GetSpaceByName, SpaceMgr, argv[3]);

    if (ConjuringSpace->Name != argv[3])
    {
        cout << "Space not found" << endl;
        return 0;
    }

    cout << "Entering space..." << endl;
    // Enter space
    common::String EntryResult = CallAsyncFunction<common::String>(&SpaceManager::EnterSpace, SpaceMgr, ConjuringSpace->Id);

    if (EntryResult != "Success")
    {
        cout << "Failed to enter space" << endl;
        return 0;
    }
    
    cout << "Waiting for space entities to be retrieved..." << endl;
    // Wait for entities to be retrieved
	bool EntitiesRetrieved = CallAsyncFunction<bool>(&SpaceManager::WaitForEntityRetrieval, SpaceMgr);
    
    if (!EntitiesRetrieved)
    {
        cout << "Failed to retrieve space entities" << endl;
        return 0;
    }

    cout << "Finding \"" << ComponentName << "\" component..." << endl;
    // Get component by name 
    //multiplayer::ComponentBase* Component = SpaceMgr->GetComponentByName(ComponentName, EntityName);
    multiplayer::ComponentBase* Component = SpaceMgr->GetComponentByName(argv[4], argv[5]);

	if (Component == nullptr)
	{
		cout << "Component not found" << endl;
		return 0;
	}

	// Set text component
    if (Component->GetComponentType() != multiplayer::ComponentType::Text)
    {
        cout << "Component type is not Text" << endl;
        return 0;
    }

    multiplayer::TextSpaceComponent* TextComponent = dynamic_cast<csp::multiplayer::TextSpaceComponent*>(Component);    
	
    cout << "Current text: " << TextComponent->GetText() << endl;
    
    //bool UpdateStatus = CallAsyncFunction<bool>(&ComponentManager::SetText, ComponentMgr, TextComponent, "Hello, World!");
    bool UpdateStatus = CallAsyncFunction<bool>(&ComponentManager::SetText, ComponentMgr, TextComponent, argv[6]);
    
    cout << "Set text result: " << (UpdateStatus ? "Success" : "Failure") << endl;

    return 0;
}