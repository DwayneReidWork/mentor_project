from setuptools import setup, find_packages

setup(
    name="chessC",
    version="0.1.0",
    packages=find_packages(),
    entry_points={
        'console_scripts': [
            'chessc = chess_client.__main__:main',
        ],
    },
)
