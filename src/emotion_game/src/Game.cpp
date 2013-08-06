#include <Game.h>

#include <ros/ros.h>
#include <std_srvs/Empty.h>

#define START_SPEECH_RECOGNITION_NAME "nao_speech/start_recognition"
#define STOP_SPEECH_RECOGNITION_NAME "nao_speech/stop_recognition"

const Phrase Game::NULL_PHRASE = Phrase("");

void Game::introduction(void)
{
	//Perform start and instruction phrases/actions, etc
	std::vector<Phrase> phraseVector;
	if (getGameSettings().getPhraseVector(START_KEY, phraseVector)){
		const Phrase& phrase = sayAny(phraseVector);

		if (phrase.getNumberOfBehaviors() != 0){
			std::string behavior = phrase.getRandomBehaviorName();

			_naoControl.perform(behavior);
		}
	}
	sleep(_settings.getWait());

	if (getGameSettings().getPhraseVector(INSTRUCTION_KEY, phraseVector)){
		const Phrase& phrase = sayAny(phraseVector);

		if (phrase.getNumberOfBehaviors() != 0){
			std::string behavior = phrase.getRandomBehaviorName();

			_naoControl.perform(behavior);
		}
	}
	sleep(_settings.getWait());

	_currentState = PERFORM_EMOTION;
}

void Game::performEmotion(void)
{
	const std::vector<Behavior>& behaviorVector = _settings.getBehaviorVector();

	//Find a new random behavior to perform
	int index = 0;
	while (true){
		index = rand() % behaviorVector.size();
		const Behavior& ref = behaviorVector[index];

		if (_performedBehavior == NULL || ref.getActualName() != _performedBehavior->getActualName())
			break;
	}

	const Behavior& ref = behaviorVector[index];
	_naoControl.perform(ref.getName());

	if (_performedBehavior != NULL)
		delete _performedBehavior;

	_performedBehavior = new Behavior(ref);
}

bool Game::startSpeechRecognition()
{
	std::cout << "Starting speech recognition." << std::endl;

	ros::NodeHandle nh;

	ros::ServiceClient client = nh.serviceClient<std_srvs::Empty>(START_SPEECH_RECOGNITION_NAME);
	std_srvs::Empty emptySrv;

	return client.call(emptySrv);
}

bool Game::stopSpeechRecognition()
{
	std::cout << "Stopping speech recognition." << std::endl;

	ros::NodeHandle nh;

	ros::ServiceClient client = nh.serviceClient<std_srvs::Empty>(STOP_SPEECH_RECOGNITION_NAME);
	std_srvs::Empty emptySrv;

	return client.call(emptySrv);
}

const Phrase& Game::sayRandParts(const Phrase& phrase, std::list<std::string> parts)
{
	int numParts = phrase.amountOfParts();

	if (phrase.amountOfParts() <= parts.size()){
		//Select random numParts to use as parts
		std::list<std::string> usedParts;

		while (numParts != 0){
			int rndIndex = rand() % parts.size();

			std::string val;

			int i = 0;
			std::list<std::string>::iterator it = parts.begin();
			while (it != parts.end()){
				if (i == rndIndex){
					val = *it;

					break;
				}

				i++;
				it++;
			}

			parts.remove(val);
			usedParts.push_back(val);

			numParts--;
		}

		_naoControl.say(phrase.getPhrase(usedParts));

		return phrase;
	}

	return NULL_PHRASE;
}

const Phrase& Game::say(const Phrase& phrase)
{
	_naoControl.say(phrase.getPhrase());
	return phrase;
}

const Phrase& Game::say(const Phrase& phrase, const std::list<std::string> parts)
{
	if (parts.size() >= phrase.amountOfParts()){
		_naoControl.say(phrase.getPhrase(parts));
	}

	return phrase;
}

const Phrase& Game::sayRandParts(const Phrase& phrase, const std::string& required, std::list<std::string> parts)
{
	int numParts = phrase.amountOfParts();

	if (phrase.amountOfParts() <= parts.size()){
		int requiredIndex = rand() % numParts;

		//Select random numParts to use as parts
		std::list<std::string> usedParts;

		while (numParts != 0){
			// Index for the required string has been reached, insert
			if (phrase.amountOfParts() - numParts == requiredIndex){
				usedParts.push_back(required);
				numParts--;

				continue;
			}

			int rndIndex = rand() % parts.size();

			std::string val;

			int i = 0;
			std::list<std::string>::iterator it = parts.begin();
			while (it != parts.end()){
				if (i == rndIndex){
					val = *it;

					break;
				}

				i++;
				it++;
			}

			parts.remove(val);
			usedParts.push_back(val);

			numParts--;
		}

		_naoControl.say(phrase.getPhrase(usedParts));
		return phrase;
	}

	return NULL_PHRASE;
}

const Phrase& Game::sayAny(const std::vector<Phrase>& phraseVector)
{
	int index = rand() % phraseVector.size();

	const Phrase& actual = phraseVector[index];
	if (actual.amountOfParts() == 0){
		_naoControl.say(actual.getPhrase());

		return actual;
	}

	return NULL_PHRASE;
}

const Phrase& Game::sayAny(const std::vector<Phrase>& phraseVector, const std::list<std::string>& parts)
{
	int index = rand() % phraseVector.size();

	const Phrase& actual = phraseVector[index];

	if (actual.amountOfParts() <= parts.size()){
		_naoControl.say(actual.getPhrase(parts));

		return actual;
	}

	return NULL_PHRASE;
}

const Phrase& Game::sayAnyRandParts(const std::vector<Phrase>& phraseVector, const std::list<std::string>& parts)
{
	int index = rand() % phraseVector.size();

	const Phrase& actual = phraseVector[index];

	if (actual.amountOfParts() <= parts.size())
		return sayRandParts(actual, parts);

	return NULL_PHRASE;
}

const Phrase& Game::sayAnyRandParts(const std::vector<Phrase>& phraseVector, const std::string& required, const std::list<std::string>& parts)
{
	int index = rand() % phraseVector.size();

	const Phrase& actual = phraseVector[index];

	if (actual.amountOfParts() <= parts.size())
		return sayRandParts(actual, required, parts);

	return NULL_PHRASE;
}
