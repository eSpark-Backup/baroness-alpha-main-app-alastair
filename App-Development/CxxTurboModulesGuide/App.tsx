import React, { useEffect, useState } from 'react';
import {
  SafeAreaView,
  ScrollView,
  StatusBar,
  StyleSheet,
  Text,
  useColorScheme,
  View,
  Animated,
} from 'react-native';
import { Colors } from 'react-native/Libraries/NewAppScreen';
import NativeSampleModule from './tm/NativeSampleModule';

function App(): React.JSX.Element {
  const [fuelPercentage, setFuelPercentage] = useState(0);
  const [speedometerRPM, setspeedometerRPM] = useState(0);
  const [tachometerRPM, settachometerRPM] = useState(0);
  const isDarkMode = useColorScheme() === 'dark';
  const backgroundStyle = {
    backgroundColor: isDarkMode ? Colors.darker : Colors.lighter,
  };

  useEffect(() => {
    NativeSampleModule.getVehicleData((result) => {
      // Parse the JSON string to extract the values
      const data = JSON.parse(result);
      setFuelPercentage(data.fuel);
      setspeedometerRPM(data.speedometerRPM);
      settachometerRPM(data.tachometerRPM);
    });
  }, []);

  return (
    <SafeAreaView style={backgroundStyle}>
      <StatusBar barStyle={isDarkMode ? 'light-content' : 'dark-content'} backgroundColor={backgroundStyle.backgroundColor} />
      <ScrollView contentInsetAdjustmentBehavior="automatic" style={backgroundStyle}>
        <View style={styles.container}>
          <Text style={styles.title}>Fuel Status</Text>
          <View style={styles.progressContainer}>
            <Animated.View style={[styles.progressBar, { width: `${fuelPercentage}%` }]} />
          </View>
          <Text style={styles.fuelText}>
            {`Remaining Fuel: ${fuelPercentage}%`}
          </Text>
        </View>

        <View style={styles.container}>
          <Text style={styles.title}>Tachometer</Text>
          <Text style={styles.fuelText}>
            {`RPM: ${tachometerRPM}`}
          </Text>
        </View>

        <View style={styles.container}>
          <Text style={styles.title}>SpeedoMeter</Text>
          <Text style={styles.fuelText}>
            {`RPM: ${speedometerRPM}`}
          </Text>
        </View>

      </ScrollView>
    </SafeAreaView>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    justifyContent: 'center',
    alignItems: 'center',
    padding: 20,
    backgroundColor: 'transparent',
  },
  title: {
    fontSize: 32,
    fontWeight: 'bold',
    marginBottom: 20,
  },
  progressContainer: {
    width: '100%',
    height: 25,
    borderRadius: 15,
    backgroundColor: Colors.lightGray,
    overflow: 'hidden',
    marginBottom: 20,
  },
  progressBar: {
    height: '100%',
    backgroundColor: Colors.primary,
    borderRadius: 15,
  },
  fuelText: {
    fontSize: 20,
    fontWeight: '600',
    color: Colors.primary,
  },
});

export default App;
