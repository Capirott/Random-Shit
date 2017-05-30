import datetime
from django.utils import timezone
from django.test import TestCase
from .models import Student, School

class StudentMethodTests(TestCase):
    def test_was_registered_recently(self):
        """
            was_registered_recently() should return True for Students whose registration_date is less than a month, otherwise false.
        """
        time = timezone.now() - datetime.timedelta(days=30)
        student = Student(name='Testing Student', registration_date=time, gender='M')
        self.assertIs(student.was_registered_recently(), True)
        time = timezone.now() + datetime.timedelta(days=30)
        student = Student(name='Testing Student', registration_date=time, gender='M')
        self.assertIs(student.was_registered_recently(), False)
        

    


