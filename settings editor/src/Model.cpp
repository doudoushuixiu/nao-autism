#include <Model.h>
#include <Keys.h>

#include <fstream>
#include <stdexcept>

void addPhraseMapToDoc(Json::Value& root, std::map<std::string, PhraseGroupData>& map);
void addBehaviorListToDoc(Json::Value& root, std::list<BehaviorData>& behaviorData);
void addStringArrayToDoc(Json::Value& root, std::list<std::string>& list);

std::map<std::string, PhraseGroupData> loadPhraseGroups(Json::Value& root);
std::list<BehaviorData> loadBehaviorData(Json::Value& root);
std::string loadBehaviorActualName(Json::Value& root);
std::list<std::string> loadBehaviorNames(Json::Value& root);
int loadClassification(Json::Value& root);

void Model::open(const std::string& location)
{
	if (location != ""){
		//Load file into 'buffer'
		std::string jsonData;

		std::fstream ifs;
		ifs.open(location.c_str(), std::fstream::in);

		ifs.seekg(0, std::ios::end);
		jsonData.resize(ifs.tellg());
		ifs.seekg(0, std::ios::beg);

		ifs.read(&jsonData[0], jsonData.size());
		ifs.close();

		Json::Reader jsonReader;

		Json::Value doc;
		if (jsonReader.parse(jsonData, doc)){
			loadData(doc);

			_fileLocation = location;
		}
	}
}

void Model::save()
{
	std::cout << "Save..." << std::endl;
	saveData(_fileLocation);
}

void Model::saveAs(const std::string& location)
{
	std::cout << "Save..." << std::endl;
	saveData(location);
}

void Model::saveData(const std::string& location)
{
	//Create new JSON document
	Json::Value doc(Json::objectValue);

	addPhraseMapToDoc(doc, _generalPhraseMap);
	addBehaviorListToDoc(doc, _gameBehaviorsDataList);

	//Add base settings to JSON document
	Json::Value& baseSettings = doc[BASE_SETTINGS_KEY];
	Json::Value& maxPromptVal = baseSettings[MAX_PROMPT_KEY];
	maxPromptVal = _maxPrompts;

	Json::Value& timeoutVal = baseSettings[TIMEOUT_SETTING_KEY];
	timeoutVal = _timeout;

	Json::Value& speechWaitVal = baseSettings[SPEECH_WAIT_SETTING_KEY];
	speechWaitVal = _wait;

	Json::Value& rewardBehavior = doc[REWARD_BEHAVIOR_LIST_KEY];
	Json::Value& rewardBehaviorNames = rewardBehavior[BEHAVIOR_NAME_KEY];
	addStringArrayToDoc(rewardBehaviorNames, _rewardBehaviorDataList);

	Json::Value& guessGameSettings = doc[GUESS_GAME_KEY];
	addPhraseMapToDoc(guessGameSettings, _guessGamePhraseMap);

	Json::Value& mimicGameSettings = doc[MIMIC_GAME_KEY];
	addPhraseMapToDoc(mimicGameSettings, _mimicGamePhraseMap);

	//Generate styled json string
	Json::StyledWriter writer;
	std::string output = writer.write(doc);

	//Write generated json string to file and flush
	std::fstream fs;
	fs.open(location.c_str(), std::fstream::out);

	fs << output;
	fs.flush();

	//Close stream
	fs.close();
}

void addPhraseMapToDoc(Json::Value& root, std::map<std::string, PhraseGroupData>& map){
	Json::Value& phraseRoot = root[PHRASE_KEY];

	std::map<std::string, PhraseGroupData>::iterator it = map.begin();
	while (it != map.end()){
		std::pair<std::string, PhraseGroupData> pair = *it;

		Json::Value& current = phraseRoot[pair.first];

		//Now, add phrases and behaviors
		Json::Value& currentPhrases = current[PHRASE_KEY];
		std::list<std::string>::iterator phraseIt = pair.second.phraseVector.begin();
		while (phraseIt != pair.second.phraseVector.end()){
			std::string& phrase = *phraseIt;

			currentPhrases.append(phrase);
			phraseIt++;
		}

		Json::Value& currentBehaviors = current[BEHAVIOR_KEY];
		std::list<std::string>::iterator behaviorIt = pair.second.behaviorVector.begin();
		while (behaviorIt != pair.second.behaviorVector.end()){
			std::string& behavior = *behaviorIt;

			currentBehaviors.append(behavior);
			behaviorIt++;
		}

		it++;
	}
}

void addBehaviorListToDoc(Json::Value& root, std::list<BehaviorData>& behaviorData)
{
	Json::Value& behaviorRoot = root[BEHAVIOR_KEY];

	std::list<BehaviorData>::iterator it = behaviorData.begin();
	while (it != behaviorData.end()){
		BehaviorData& data = *it;

		Json::Value newBehavior(Json::objectValue);

		Json::Value& newBehaviorActualName = newBehavior[BEHAVIOR_ACTUAL_KEY];
		newBehaviorActualName = data._actualName;

		Json::Value& newBehaviorNames = newBehavior[BEHAVIOR_NAME_KEY];
		addStringArrayToDoc(newBehaviorNames, data._behaviorNames);

		Json::Value& newBehaviorClassification = newBehavior[BEHAVIOR_CLASSIFICATION_KEY];
		newBehaviorClassification = data._classification;

		behaviorRoot.append(newBehavior);

		it++;
	}
}

void addStringArrayToDoc(Json::Value& root, std::list<std::string>& list)
{
	std::list<std::string>::iterator it = list.begin();
	while (it != list.end()){
		std::string& str = *it;

		root.append(str);

		it++;
	}
}

void Model::retrieveGeneralPhraseGroup(const std::string& key) const
{
	try{
		const PhraseGroupData& data = _generalPhraseMap.at(key);

		emit generalPhraseGroupRetrieved(data);
	}catch(std::out_of_range& ex){  }
}

void Model::retrieveGuessGamePhraseGroup(const std::string& key) const
{
	try{
		const PhraseGroupData& data = _guessGamePhraseMap.at(key);

		emit guessGamePhraseGroupRetrieved(data);
	}catch(std::out_of_range& ex){  }
}

void Model::retrieveMimicGamePhraseGroup(const std::string& key) const
{
	try{
		const PhraseGroupData& data = _mimicGamePhraseMap.at(key);

		emit mimicGamePhraseGroupRetrieved(data);
	}catch(std::out_of_range& ex){  }
}

void Model::addGeneralPhrase(const std::string& key, const std::string& phrase)
{
	try{
		PhraseGroupData& data = _generalPhraseMap.at(key);

		data.phraseVector.push_back(phrase);
	}catch(std::out_of_range& ex){  }
}

void Model::addGuessGamePhrase(const std::string& key, std::string& phrase)
{
	try{
		PhraseGroupData& data = _guessGamePhraseMap.at(key);

		data.phraseVector.push_back(phrase);
	}catch(std::out_of_range& ex){  }
}

void Model::addMimicGamePhrase(const std::string& key, std::string& phrase)
{
	try{
		PhraseGroupData& data = _mimicGamePhraseMap.at(key);

		data.phraseVector.push_back(phrase);
	}catch(std::out_of_range& ex){  }
}

void Model::addGeneralPhraseBehavior(const std::string& key, const std::string& behavior)
{
	try{
		PhraseGroupData& data = _generalPhraseMap.at(key);

		data.behaviorVector.push_back(behavior);
	}catch(std::out_of_range& ex){  }
}

void Model::addGuessGamePhraseBehavior(const std::string& key, const std::string& behavior)
{
	try{
		PhraseGroupData& data = _guessGamePhraseMap.at(key);

		data.behaviorVector.push_back(behavior);
	}catch(std::out_of_range& ex){  }
}

void Model::addMimicGamePhraseBehavior(const std::string& key, const std::string& behavior)
{
	try{
		PhraseGroupData& data = _mimicGamePhraseMap.at(key);

		data.behaviorVector.push_back(behavior);
	}catch(std::out_of_range& ex){  }
}

void Model::retrieveGameBehavior(const std::string& name) const
{
	std::list<BehaviorData>::const_iterator it = _gameBehaviorsDataList.begin();
	while (it != _gameBehaviorsDataList.end()){
		const BehaviorData& data = *it;

		if (data._actualName == name){
			emit gameBehaviorRetrieved(data);
			return;
		}

		it++;
	}
}

void Model::loadData(Json::Value& docRoot){
	//Load base settings
	Json::Value& baseSettings = docRoot[BASE_SETTINGS_KEY];
	if (baseSettings != Json::Value::null){
		Json::Value& timeoutVal = baseSettings[TIMEOUT_SETTING_KEY];
		_timeout = timeoutVal.asInt();

		Json::Value& maxPromptVal = baseSettings[MAX_PROMPT_KEY];
		_maxPrompts = maxPromptVal.asInt();

		Json::Value& waitVal = baseSettings[SPEECH_WAIT_SETTING_KEY];
		_wait = waitVal.asInt();
	}

	//Load general phrase map
	Json::Value& generalPhrases = docRoot[PHRASE_KEY];
	if (generalPhrases != Json::Value::null){
		//Found general phrases, load them into phrase groups
		_generalPhraseMap = loadPhraseGroups(generalPhrases);
	}

	//Load guess game phrase map
	Json::Value& guessGamePhrases = docRoot[GUESS_GAME_KEY][PHRASE_KEY];
	if (guessGamePhrases != Json::Value::null){
		_guessGamePhraseMap = loadPhraseGroups(guessGamePhrases);
	}

	//Load mimic game phrase map
	Json::Value& mimicGamePhrases = docRoot[MIMIC_GAME_KEY][PHRASE_KEY];
	if (mimicGamePhrases != Json::Value::null){
		_mimicGamePhraseMap = loadPhraseGroups(mimicGamePhrases);
	}

	//Load reward behaviors
	Json::Value& rewardBehaviors = docRoot[REWARD_BEHAVIOR_LIST_KEY][BEHAVIOR_NAME_KEY];
	if (rewardBehaviors != Json::Value::null){
		_rewardBehaviorDataList = loadBehaviorNames(rewardBehaviors);
	}

	//Load other behaviors
	Json::Value& otherBehaviors = docRoot[BEHAVIOR_KEY];
	if (otherBehaviors != Json::Value::null){
		_gameBehaviorsDataList = loadBehaviorData(otherBehaviors);
	}

	//Fire all required signals for the new data
	update();
}

void Model::update()
{
	emit generalPhraseGroupLoaded(_generalPhraseMap);
	emit guessGamePhraseGroupLoaded(_guessGamePhraseMap);
	emit mimicGamePhraseGroupLoaded(_mimicGamePhraseMap);

	emit gameBehaviorsLoaded(_gameBehaviorsDataList);
	emit rewardBehaviorsLoaded(_rewardBehaviorDataList);
}

std::map<std::string, PhraseGroupData> loadPhraseGroups(Json::Value& root){
	std::map<std::string, PhraseGroupData> loaded;

	Json::Value::Members memberNames = root.getMemberNames();
	for (int i=0;i<memberNames.size();i++){
		std::string key = memberNames[i];

		Json::Value current = root.get(key, Json::Value::null);
		if (current != Json::Value::null){
			std::list<std::string> phrases;
			std::list<std::string> behaviors;

			Json::Value phraseArray = current.get(PHRASE_KEY, Json::Value::null);
			if (phraseArray != Json::Value::null){
				Json::Value::ArrayIndex size = phraseArray.size();

				for (int j=0;j<size;j++){
					Json::Value phraseNameVal = phraseArray.get(j, Json::Value::null);

					if (phraseNameVal != Json::Value::null){
						phrases.push_back(phraseNameVal.asString());
					}
				}
			}

			Json::Value behaviorArray = current.get(BEHAVIOR_KEY, Json::Value::null);
			if (behaviorArray != Json::Value::null){
				Json::Value::ArrayIndex size = behaviorArray.size();

				for (int j=0;j<size;j++){
					Json::Value behaviorNameVal = behaviorArray.get(j, Json::Value::null);

					if (behaviorNameVal != Json::Value::null){
						behaviors.push_back(behaviorNameVal.asString());
					}
				}
			}

			PhraseGroupData group;

			group.phraseVector = phrases;
			group.behaviorVector = behaviors;

			loaded.insert(std::pair<std::string, PhraseGroupData>(key, group));
		}
	}

	return loaded;
}

std::list<BehaviorData> loadBehaviorData(Json::Value& root){
	std::list<BehaviorData> loaded;

	Json::Value::ArrayIndex size = root.size();
	for (int i=0;i<size;i++){
		Json::Value& val = root[i];

		//Sanity check
		if (val != Json::Value::null){
			Json::Value& actualVal = val[BEHAVIOR_ACTUAL_KEY];
			std::string actual = loadBehaviorActualName(actualVal);

			Json::Value& namesVal = val[BEHAVIOR_NAME_KEY];
			std::list<std::string> names = loadBehaviorNames(namesVal);

			Json::Value& classificationVal = val[BEHAVIOR_CLASSIFICATION_KEY];
			int classification = loadClassification(classificationVal);

			BehaviorData data;
			data._actualName = actual;
			data._behaviorNames = names;
			data._classification = classification;

			loaded.push_back(data);
		}
	}

	return loaded;
}

std::string loadBehaviorActualName(Json::Value& root){
	if (root != Json::Value::null){
		return root.asString();
	}

	return "";
}

std::list<std::string> loadBehaviorNames(Json::Value& root){
	std::list<std::string> loaded;

	if (root != Json::Value::null){
		Json::Value::ArrayIndex size = root.size();
		for (int i=0;i<size;i++){
			Json::Value& current = root[i];

			if (current != Json::Value::null){
				loaded.push_back(current.asString());
			}
		}
	}

	return loaded;
}

int loadClassification(Json::Value& root){
	if (root != Json::Value::null){
		return root.asInt();
	}

	return -1;
}
